#include "Hikv3VodStream.h"
#include "x_file.h"

#define RECV_SIZE (1024 * 1024)
#define PACKET_BUFF_SIZE (1024 * 1024)
#define MAX_RECV_PACKET 8192
#define TIME_DURATION 40

CHikv3VodStream::CHikv3VodStream(void *pOwner, int nChannelNum)
: m_pRecvBuff(NULL)
, m_pPackBuff(NULL)
, m_pRead(NULL)
, m_pWrite(NULL)
, m_readFileLen(0)
, m_bEndFile(false)
, m_bFirstFile(true)
{
	m_pRingBuffer = NULL;
	m_recvSocket = NULL;
	m_recvThread = 0;
	m_parserThread = 0;
	m_bPlay = false;
	m_bPaused = false;
	m_pWrite = NULL;
	m_pRead = NULL;
	m_fileLen = 0;
	m_nChannelNum = nChannelNum;

	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[RECV_SIZE];

	if (NULL == m_pPackBuff)
		m_pPackBuff = new char[PACKET_BUFF_SIZE];

	m_nLastRecvTime = m_time.GetLocalTime(0);
	m_nDuration = TIME_DURATION;
	m_curFileName.clear();

	m_pWrite = CreateFile();
	m_pAdapter = (CHikv3Adapter *)pOwner;
}

CHikv3VodStream::~CHikv3VodStream()
{
	if (m_pRingBuffer != NULL)
		delete m_pRingBuffer;

	if (m_recvSocket != NULL)
		delete m_recvSocket;

	m_timer.Destroy();

	if (m_pRecvBuff != NULL)
		delete m_pRecvBuff;

	if (m_pPackBuff != NULL)
		delete m_pPackBuff;

	if (m_pWrite != NULL)
		fclose(m_pWrite);

	if (m_pRead != NULL)
		fclose(m_pRead);

	ClearnQue();
	J_OS::LOGINFO("CHikv3VodStream::~CHikv3VodStream()");
}

int CHikv3VodStream::Play(time_t beginTime, time_t endTime, CRingBuffer *&pRingBuffer)
{
	if (m_bPlay)
		return J_OK;

	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead) + sizeof(HikPlayByTime));
	commHead.protoType = (THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99;
	commHead.command = htonl(HIK_CMD_PLAYBYTIME);
	commHead.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(m_pAdapter->CheckSum((unsigned char*)&commHead, sizeof(HikCommHead)));

	if (m_pRingBuffer == NULL)
		m_pRingBuffer = new CRingBuffer();

	if (m_recvSocket == NULL)
	{
		m_recvSocket = new J_OS::CTCPSocket();
		m_recvSocket->Connect(m_pAdapter->GetRemoteIp(), m_pAdapter->GetRemotePort());
	}

	if (m_recvSocket->Write((char*)&commHead, sizeof(commHead)) < 0)
		return J_INVALID_DEV;

	HikPlayByTime playByTime;
	playByTime.channelNum = htonl(m_nChannelNum);
	Convert2HikTime(beginTime, playByTime.beginTime);
	Convert2HikTime(endTime, playByTime.endTime);

	if (m_recvSocket->Write((char *)&playByTime, sizeof(HikPlayByTime)) < 0)
		return J_INVALID_DEV;

	HikRetHead retHead;
	if (m_recvSocket->Read((char *)&retHead, sizeof(HikRetHead)) < 0)
			return J_INVALID_DEV;

	HikPlayByTimeRet playByTimeRet;
	if (m_recvSocket->Read((char *)&playByTimeRet, sizeof(HikPlayByTimeRet)) < 0)
		return J_INVALID_DEV;

	struct CmdPlay
    {
		HikCommHead cmdHeader;
		int offset;
	} cmdPlay;

	memset(&cmdPlay.cmdHeader, 0, sizeof(HikCommHead));
	cmdPlay.cmdHeader.len = htonl(sizeof(HikCommHead) + sizeof(int));
	cmdPlay.cmdHeader.protoType = /*(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : */99;
	cmdPlay.cmdHeader.command = htonl(HIK_CMD_STARTPLAY);
	cmdPlay.cmdHeader.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(cmdPlay.cmdHeader.clientIP, cmdPlay.cmdHeader.clientMAC);
	cmdPlay.cmdHeader.checkSum = htonl(m_pAdapter->CheckSum((unsigned char*)&cmdPlay.cmdHeader, sizeof(HikCommHead)));
	cmdPlay.offset = htonl(0);

	if (m_recvSocket->Write((char*)&cmdPlay, sizeof(CmdPlay)) < 0)
		return J_INVALID_DEV;

	m_timer.Create(3 * 1000, CHikv3VodStream::OnTimer, this);

	m_bPlay = true;
	pthread_create(&m_recvThread, NULL, CHikv3VodStream::WorkThread, this);
	pthread_create(&m_parserThread, NULL, CHikv3VodStream::ParserThread, this);

	pRingBuffer = m_pRingBuffer;

	J_OS::LOGINFO("CHikv3VodStream::Play Sucess");

	return J_OK;
}

int CHikv3VodStream::Stop()
{
	if (!m_bPlay)
		return J_OK;

	m_bPlay = false;
	pthread_cancel(m_recvThread);
	pthread_join(m_recvThread, NULL);

	pthread_cancel(m_parserThread);
	pthread_join(m_parserThread, NULL);

	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}

	m_timer.Destroy();

	if (m_pRingBuffer != NULL)
	{
		delete m_pRingBuffer;
		m_pRingBuffer = NULL;
	}

	m_parser.Deinit();

	J_OS::LOGINFO("CHikv3VodStream::Stop Stop this = %d", this);

	return J_OK;
}

int CHikv3VodStream::Pause()
{
	m_bPaused = !m_bPaused;

	return J_OK;
}

int CHikv3VodStream::SetSpeed(int nSpeed, bool bFlag)
{
	if (nSpeed == 0 || nSpeed == 1)
	{
		m_nDuration = TIME_DURATION;
		return J_OK;
	}

	double nTimes = sqrt((double)nSpeed);
	if (bFlag)
		m_nDuration = TIME_DURATION / nTimes;
	else
		m_nDuration = TIME_DURATION * nTimes;

	return J_OK;
}

int CHikv3VodStream::SetPos()
{
	return J_OK;
}

void CHikv3VodStream::ExchangeData()
{
	if (NULL == m_recvSocket)
		return;

    static HikCommHead commHead;
    memset(&commHead, 0, sizeof(HikCommHead));
    commHead.len = htonl(sizeof(HikCommHead));
    commHead.protoType = (THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99;
    commHead.command = htonl(HIK_CMD_FILE_EXCHANGE);
    commHead.userId = htonl(m_pAdapter->GetUserId());
    m_pAdapter->GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
    commHead.checkSum = htonl(m_pAdapter->CheckSum((unsigned char*)&commHead, sizeof(HikCommHead)));

    if (m_recvSocket->Write((char*)&commHead, sizeof(commHead)) < 0)
    {
    	J_OS::LOGINFO("CHikv3VodStream::ExchangeData ExchangeData error");
    }

	struct CmdPlay
    {
		HikCommHead cmdHeader;
		int offset;
	} cmdPlay;

	memset(&cmdPlay.cmdHeader, 0, sizeof(HikCommHead));
	cmdPlay.cmdHeader.len = htonl(sizeof(HikCommHead) + sizeof(int));
	cmdPlay.cmdHeader.protoType = /*(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : */99;
	cmdPlay.cmdHeader.command = htonl(HIK_CMD_STARTPLAY);
	cmdPlay.cmdHeader.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(cmdPlay.cmdHeader.clientIP, cmdPlay.cmdHeader.clientMAC);
	cmdPlay.cmdHeader.checkSum = htonl(m_pAdapter->CheckSum((unsigned char*)&cmdPlay.cmdHeader, sizeof(HikCommHead)));
	cmdPlay.offset = htonl(0);

	if (m_recvSocket->Write((char*)&cmdPlay, sizeof(CmdPlay)) < 0)
    {
    	J_OS::LOGINFO("CHikv3VodStream::ExchangeData Play error");
    }

   //J_OS::LOGINFO("CHikv3VodStream::ExchangeData ExchangeData");
}

void CHikv3VodStream::OnWork()
{
	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
	HikRecvFileHead recvFileHead;
	while (true)
	{
		int nLen = 0;
		int nRecvLen = 0;
		memset(&recvFileHead, 0, sizeof(HikRecvFileHead));
		nRecvLen = m_recvSocket->Read_n((char *)&recvFileHead, sizeof(HikRecvFileHead));
		if (nRecvLen < 0)
		{
			J_OS::LOGINFO("CHikv3VodStream::OnWork recv head error errno = %d", errno);
				break;
		}

		recvFileHead.length = ntohl(recvFileHead.length);
		recvFileHead.state = ntohl(recvFileHead.state);

		if (recvFileHead.state == NEEDRECVDATA)
		{
			//TLock(m_fileLock);
			int totleLen = recvFileHead.length - sizeof(HikRecvFileHead);
			nLen = m_recvSocket->Read_n(m_pRecvBuff, totleLen);
			if (m_fileLen >= 100 * 1024 * 1024)
			{
				fclose(m_pWrite);
				m_pWrite = NULL;
			}

			if (m_pWrite == NULL)
			{
				m_pWrite = CreateFile();
				m_fileLen = 0;
				m_bFirstFile = false;
			}
			if (fwrite(m_pRecvBuff, 1, nLen, m_pWrite) > 0)
			{
				m_fileLen += nLen;
				fflush(m_pWrite);
			}
			//TUnlock(m_fileLock);
		}
		else if (recvFileHead.state == NEEDRECVFILEHEAD)
		{
			HikPlayByTimeHead playByTimeHead;
			if (m_recvSocket->Read((char *)&playByTimeHead, sizeof(HikPlayByTimeHead)) < 0)
				break;

			playByTimeHead.headLength = ntohl(playByTimeHead.headLength);
			playByTimeHead.fileLength = ntohl(playByTimeHead.fileLength);
			playByTimeHead.totleTime = ntohl(playByTimeHead.totleTime);

			if (playByTimeHead.headLength > 0)
			{
				if (m_recvSocket->Read((char *)m_pRecvBuff, playByTimeHead.headLength) < 0)
					break;

				/*NVRStreamHeader streamHeader;
				streamHeader.dataLen = playByTimeHead.headLength;
				streamHeader.frameType = HEADER_T;
				m_pRingBuffer->PushBuffer(m_pRecvBuff, streamHeader);
				m_parser.Init(m_pRecvBuff);*/
			}
		}
		else if (recvFileHead.state == BYTIME_ALLFILEEND)
		{
			J_OS::LOGINFO("CHikv3VodStream::OnWork play BYTIME_ALLFILEEND");
			m_timer.Destroy();
			m_bEndFile = true;

			break;
		}
		else
		{
			J_OS::LOGINFO("CHikv3VodStream::OnWork() file state = %d", recvFileHead.state);
		}
		pthread_testcancel();
	}
	J_OS::LOGINFO("CHikv3VodStream::OnWork pthread_exit");
}

void CHikv3VodStream::OnParser()
{
	//char *pReadBuff = new char[8 * 1024];
	char pReadBuff[8 * 1024] = {0};
	bool bParser = true;
	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
	while (true)
	{
		if (m_bPaused)
		{
			usleep(10000);
			continue;
		}

		if (m_time.GetLocalTime(0) - m_nLastRecvTime >= m_nDuration)
		{
			int nPackLen = 0;
			int nFrameType;
			bool bGetOneFrameVideo = false;
			do
			{
				/*m_parser.GetOnePacket(m_pPackBuff, nPackLen, nFrameType);
				if (nPackLen > 0)
				{
					NVRStreamHeader streamHeader;
					streamHeader.dataLen = nPackLen;
					streamHeader.frameType = nFrameType;

					m_pRingBuffer->PushBuffer(m_pPackBuff, streamHeader);
				}
				else
				{
					//TLock(m_fileLock);
					if (m_pRead == NULL)
					{
						if (m_fileQue.size() > 0)
						{
							m_curFileName = m_fileQue.front();
							m_pRead = fopen(m_curFileName.c_str(), "rb+");
							if (m_pRead == NULL)
							{
								J_OS::LOGINFO("m_pRead == NULL, %s", m_curFileName.c_str());
								continue;
							}
							fseek(m_pRead, 0, SEEK_END);
							m_readFileLen = ftell(m_pRead);
							fseek(m_pRead, 0, SEEK_SET);

							m_fileQue.pop();
						}
					}
					if (m_bFirstFile)
					{
						fflush(m_pRead);
						int nOffSet = ftell(m_pRead);
						fseek(m_pRead, 0, SEEK_END);
						m_readFileLen = ftell(m_pRead);
						fseek(m_pRead, nOffSet, SEEK_SET);
					}
					if (m_readFileLen > 8 * 1024)
					{
						int nReadLen = 0;
						if ((nReadLen = fread(pReadBuff, 1, 8 * 1024, m_pRead)) > 0)
						{
							m_readFileLen -= nReadLen;
							m_parser.InputData(pReadBuff, nReadLen);
						}
					}
					else if (m_readFileLen > 0)
					{
						int nReadLen = 0;
						if ((nReadLen = fread(pReadBuff, 1, m_readFileLen, m_pRead)) > 0)
						{
							m_readFileLen -= nReadLen;
							m_parser.InputData(pReadBuff, nReadLen);
						}
					}
					else
					{
						if (m_pRead != NULL && !m_bFirstFile)
						{
							fclose(m_pRead);
							m_pRead = NULL;
							m_readFileLen = 0;

							char shCmd[256] = {0};
							sprintf(shCmd, "rm %s", m_curFileName.c_str());
							system(shCmd);
							m_curFileName.clear();

							if (m_bEndFile && m_fileQue.empty())
							{
								bParser = false;
								J_OS::LOGINFO("CHikVodStream::OnParser() End File");
								break;
							}
						}
					}
					//TUnlock(m_fileLock);
					continue;
				}
				if (nFrameType == VIDEO_T && nPackLen > 0)
				{
					bGetOneFrameVideo = true;
					m_nLastRecvTime = m_time.GetLocalTime(0);
				}*/
			} while (nPackLen > 0 && !bGetOneFrameVideo);
		}
		else
		{
			usleep(1000);
		}

		pthread_testcancel();
	}
	J_OS::LOGINFO("CHikv3VodStream::OnParser pthread_exit");
}

void CHikv3VodStream::Convert2HikTime(time_t utcTime, HikTime &hikTime)
{
	tm *pTime = localtime(&utcTime);
	hikTime.ulYear = htonl(pTime->tm_year + 1900);
	hikTime.ulMonth = htonl(pTime->tm_mon + 1);
	hikTime.ulDay = htonl(pTime->tm_mday);
	hikTime.ulHour = htonl(pTime->tm_hour);
	hikTime.ulMinute = htonl(pTime->tm_min);
	hikTime.ulSecond = htonl(pTime->tm_sec);
}

FILE *CHikv3VodStream::CreateFile()
{
	char tmpDir[32] = {0};
	sprintf(tmpDir, "hik%u_%d", (unsigned int)this, m_nChannelNum);
	if (access(tmpDir, F_OK) != 0)
	{
		if (mkdir(tmpDir, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
		{
			J_OS::LOGINFO("CHikVodStream::CreateFile mkdir error, errno = %d", errno);
			return NULL;
		}
	}

	CTime curTime;
	char fileName[128] = {0};
	sprintf(fileName, "%s/%s_%d.mp4", tmpDir, curTime.GetLocalTime().c_str(), (unsigned int)this);

	FILE *fp = fopen(fileName, "wb+");
	if (fp != NULL)
	{
		m_fileQue.push(fileName);
		return fp;
	}
	J_OS::LOGINFO("CHikVodStream::CreateFile fopen error, fileName = %d", fileName);

	return NULL;
}

void CHikv3VodStream::ClearnQue()
{
	char tmpDir[32] = {0};
	sprintf(tmpDir, "hik%u_%d", (unsigned int)this, m_nChannelNum);
	if (access(tmpDir, F_OK) != 0)
	{
			J_OS::LOGINFO("CHikVodStream::ClearnQue no Dir, %s", tmpDir);
			return;
	}

	char shCmd[32] = {0};
	sprintf(shCmd, "rm -rf %s", tmpDir);
	system(shCmd);
}
