#if (defined(__WIN32__) || defined(_WIN32)) && !defined(_WIN32_WCE)
#include <io.h>
#include <fcntl.h>
#endif
#include "GroupsockHelper.hh"
#include "OutputFile.hh"
#include "H264VideoRTPSource.hh"

#include "H264Frame.h"

////////// H264Frame //////////

CH264Frame::CH264Frame(UsageEnvironment& env, unsigned bufferSize)
					   : MediaSink(env), nBufferSize(bufferSize), nFrameNum(0)
{
	fBuffer = new unsigned char[nBufferSize];
	Clean();
}

CH264Frame::~CH264Frame() 
{
	if (NULL != fBuffer)
	{
		delete[] fBuffer;
		fBuffer = NULL;
	}	
}

CH264Frame* CH264Frame::CreateNew(UsageEnvironment& env, unsigned bufferSize)
{
	return new CH264Frame(env, bufferSize);
}

Boolean CH264Frame::continuePlaying() 
{
	if (fSource == NULL)
		return False;

	MakeH264FrameFlag(&pWriteBuffer);
	fSource->getNextFrame(pWriteBuffer, nBufferSize - nUsedBuffSize, afterGettingFrame, this, onSourceClosure, this);

	return True;
}

void CH264Frame::afterGettingFrame(void* clientData, 
								   unsigned frameSize,
								   unsigned numTruncatedBytes,
								   timeval presentationTime,
								   unsigned /*durationInMicroseconds*/) 
{
	CH264Frame* sink = (CH264Frame*)clientData;
	sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime);
}

void CH264Frame::afterGettingFrame(unsigned frameSize,
								   unsigned numTruncatedBytes,
								   timeval presentationTime) 
{
	static int nFrameTotailNum = 100;
	
	// 判断是否缓冲区太小
	if (numTruncatedBytes > 0) 
	{
		envir() << "H264Frame::afterGettingFrame(): The input frame data was too large for our buffer size ("
			<< nBufferSize << ").  "
			<< numTruncatedBytes << " bytes of trailing data was dropped!  Correct this by increasing the \"bufferSize\" parameter in the \"createNew()\" call to at least "
			<< nBufferSize + numTruncatedBytes << "\n";
	}

	// 处理帧数据，然后调用回调函数,最后清空缓冲区
	bool bIFrame = false;
	nUsedBuffSize += frameSize;

	if (((pWriteBuffer[0] & I_FRAME_HEAD_NO) == I_FRAME_HEAD_FIRST) 
		|| ((pWriteBuffer[0] & I_FRAME_HEAD_NO) == I_FRAME_HEAD_SECOND))
	{
		pWriteBuffer += frameSize;		// 直到65(即I帧)之后才写入文件
	}
	else
	{
		if ((pWriteBuffer[0] & I_FRAME_HEAD_NO) == I_FRAME_HEAD_THIRD)
		{
			bIFrame = true;		// I帧
		}
		++nFrameNum;

		if (NULL != m_pFunCallBack)
		{
			m_pFunCallBack(fBuffer, nUsedBuffSize, bIFrame, nFrameNum, presentationTime, false, pFunCallBackData);
		}
		Clean();
	}

	// 测试主动暂停
// 	if (--nFrameTotailNum < 1)
// 	{
// 		this->stopPlaying();
// 	}

	continuePlaying();
}


void CH264Frame::MakeH264FrameFlag( unsigned char * * pBuff )
{
	unsigned char const start_code[4] = {0x00, 0x00, 0x00, 0x01};
	memcpy(*pBuff, start_code, sizeof(start_code));
	*pBuff += sizeof(start_code);
	nUsedBuffSize += sizeof(start_code);
}

void CH264Frame::Clean( void )
{
	memset(fBuffer, 0, nBufferSize * sizeof(char));
	pWriteBuffer = fBuffer;
	nUsedBuffSize = 0;
}
