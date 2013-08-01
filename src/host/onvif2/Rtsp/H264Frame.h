/**
*  Copyright (c) 2013, 成都荣耀科技有限公司(http://www.ronyao.com/)
*  All rights reserved.
*
*  @file        H264Frame.h
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/24 17:34
*  @version     ver 1.0.0.1
*
*  @brief       取出视频帧并回调外部函数处理
*  @note        无
*
*   v1.0.0.1    2013/07/24 17:34    完成基础代码
*/

#ifndef __H264Frame_head__
#define __H264Frame_head__

#ifndef _MEDIA_SINK_HH
#include "MediaSink.hh"
#endif

/** 默认缓冲区大小 */
#define EXPECTED_BUFF_SIZE (1024 * 1024)


/** 回调原型 */
typedef bool(* pRtspFrameCallBack)(void * pRtspDataBuff, 
								unsigned int nRtspDataBuffSize, 
								bool bIFrame, 
								unsigned int nFrameNum,
								timeval presentationTime, 
								bool bBroken,
								void * lpVoid);

/**
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/24 18:07
*  @class       CH264Frame
*  @brief       取出H264帧并调外部回调函数
*  @note        无
*/
class CH264Frame: 
	public MediaSink 
{
public:
	typedef enum _tagIFrameHeadFlag
	{
		I_FRAME_HEAD_FIRST = 7,		/** I帧头部一(0x67) */
		I_FRAME_HEAD_SECOND = 8,	/** I帧头部二(0x68) */
		I_FRAME_HEAD_THIRD = 5,		/** I帧头部三(0x65) */
		I_FRAME_HEAD_NO = 31		/** I帧头部与值 */
	}IFrameHeadFlag;

	static CH264Frame* CreateNew(UsageEnvironment& env, unsigned bufferSize = EXPECTED_BUFF_SIZE);

	/* 回调函数地址 */
	pRtspFrameCallBack m_pFunCallBack;

	/* 回调函数外部数据 */
	void * pFunCallBackData;

protected:
	CH264Frame(UsageEnvironment& env, unsigned bufferSize);
	virtual ~CH264Frame(void);

    /**
    *  @date        2013/07/24 18:08
    *  @brief       取下一帧
    *  @return      成功返回true，否则为false
    */
	virtual Boolean continuePlaying(void);

	virtual void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes, timeval presentationTime);

	static void afterGettingFrame(void* clientData, 
		unsigned frameSize,
		unsigned numTruncatedBytes,
		timeval presentationTime,
		unsigned durationInMicroseconds);

private:
	// 写入H264帧前四个字节头部。写入之后，指针会移至尾部备写入其他数据。
	void MakeH264FrameFlag(unsigned char ** pBuff);

	// 初始化资源
	void Clean(void);

private:
	// 分配的空间大小
	unsigned nBufferSize;

	// 缓冲区首地址
	unsigned char* fBuffer;

	// 写入缓冲区指针
	unsigned char * pWriteBuffer;

	// 已用缓冲区长度
	unsigned nUsedBuffSize;

	// 帧个数
	int nFrameNum;
};

#endif // __H264Frame_head__
