#ifndef __ONVIFSTREAM_H_
#define __ONVIFSTREAM_H_
#include "OnvifParser.h"
#include "x_asio.h"

#include <stdlib.h>
#include "Rtsp/RtspProxy.h"

#define RECV_SIZE (1024 * 1024)


class COnvifStreamBase : public J_MediaStream
{};


class COnvifStream : public J_BaseVideoStream<COnvifStreamBase>
{
public:
	COnvifStream(void *pTCPSocket, j_string_t resid);
	~COnvifStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();
	
	//Lyc添加Buff到指定队列中
	static bool AddRtspBuffDataToDeque(void * pRtspDataBuff, 
		unsigned int nRtspDataBuffSize, 
		bool bIFrame, 
		unsigned int nFrameNum,
		timeval presentationTime, 
		bool bBroken,
		void * lpVoid)
	{
		COnvifStream * pConvifStream  = (COnvifStream *)lpVoid;

		bool bRet = false;

//		memset(pConvifStream->m_pRecvBuff, 0, RECV_SIZE);
		unsigned int nTargetSize = min(nRtspDataBuffSize, RECV_SIZE);
//		memcpy(pConvifStream->m_pRecvBuff, pRtspDataBuff, nTargetSize);

		J_StreamHeader streamHeader = {0};
		streamHeader.dataLen = nTargetSize;
		streamHeader.frameType = (bIFrame ? jo_video_i_frame : jo_video_p_frame);
		streamHeader.frameNum = nFrameNum;
		streamHeader.timeStamp = presentationTime.tv_sec;

		TLock(pConvifStream->m_vecLocker);
		std::vector<CRingBuffer *>::iterator it = pConvifStream->m_vecRingBuffer.begin();
		for (; it != pConvifStream->m_vecRingBuffer.end(); it++)
		{
			//J_OS::LOGINFO("begin %lld,%lld", streamHeader.timeStamp, CTime::Instance()->GetLocalTime(0));
			//J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
			(*it)->PushBuffer(/*pConvifStream->m_pRecvBuff*/(char *)pRtspDataBuff, streamHeader);
		}
		TUnlock(pConvifStream->m_vecLocker);

		return bRet;
	}

	//Lyc 获取RTSP工作线程
	static unsigned X_JO_API RtspThread(void * pCOnvifStream);

private:
	enum 
	{
		ONVIF_READ_HEAD = 1,
		ONVIF_READ_DATA,
	};
	j_boolean_t m_bStartup;
	j_char_t *m_pRecvBuff;//[100 * 1024];

	COnvifParser m_parser;
	j_string_t m_resid;

	J_OS::TLocker_t m_locker;
	J_AsioDataBase m_asioData;
	j_int32_t m_nState;

	//Lyc
	CRtspProxy m_RtspProxy;
	CJoThread m_Thread;
};

#endif //~__ONVIFSTREAM_H_
