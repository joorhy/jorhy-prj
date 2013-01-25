#include "LiveParser.h"

unsigned int g_uiPTSFactor = 0;
int YUV422To420(uint8_t *pYUV, uint8_t *pY, uint8_t *pU, uint8_t *pV, int lWidth, int lHeight)
{
	int i,j;
	uint8_t *pYUVTemp = pYUV;
	uint8_t *pYUVTempNext = pYUV+lWidth*2;

	for(i=0; i<lHeight; i+=2)
	{
		for(j=0; j<lWidth; j+=2)
		{
			pY[j] = *pYUVTemp++;
			pY[j+lWidth] = *pYUVTempNext++;

			pU[j/2] = (*(pYUVTemp) + *(pYUVTempNext))/2;
			pYUVTemp++;
			pYUVTempNext++;

			pY[j+1] = *pYUVTemp++;
			pY[j+1+lWidth] = *pYUVTempNext++;

			pV[j/2] =(*(pYUVTemp) + *(pYUVTempNext))/2;
			pYUVTemp++;
			pYUVTempNext++;
		}
		pYUVTemp+=lWidth*2;
		pYUVTempNext+=lWidth*2;
		pY+=lWidth*2;
		pU+=lWidth/2;
		pV+=lWidth/2;
	}

	return 1;
}

CLiveParser::CLiveParser()
{
	 m_pX264Handle = NULL;
	 m_pX264Param = NULL;

	 m_iNal = 0;
	 m_pNals = NULL;

	m_pPicIn = NULL;
	m_pPicOut = NULL;

	m_pDataBuff = NULL;
	m_nDataSize = 0;
	m_dateType = J_VideoNormal;
}

CLiveParser::~CLiveParser()
{

}

int CLiveParser::Init(int nDataType)
{
	m_dateType = nDataType;

	if (m_pDataBuff == NULL)
		m_pDataBuff = new char[100 * 1024 * 1024];

	m_pX264Param = new x264_param_t;
	assert(m_pX264Param);

	//* 配置参数
	 //* 使用默认参数
	 x264_param_default(m_pX264Param);
	 //* cpuFlags
	 m_pX264Param->i_threads  = X264_SYNC_LOOKAHEAD_AUTO;//* 取空缓冲区继续使用不死锁的保证.
	 //* video Properties
	 m_pX264Param->i_width   = 640; //* 宽度.
	 m_pX264Param->i_height  = 480; //* 高度
	 m_pX264Param->i_frame_total = 0; //* 编码总帧数.不知道用0.
	 m_pX264Param->i_keyint_max = 100;
	 //* bitstream parameters
	 m_pX264Param->i_bframe  = 0;
	 m_pX264Param->b_open_gop  = 0;
	 //m_pX264Param->i_bframe_pyramid = 0;
	 //m_pX264Param->i_bframe_adaptive = X264_B_ADAPT_TRELLIS;

	 //* 宽高比,有效果,但不是想要的.
	 //m_pX264Param->vui.i_sar_width = 1080;
	 //m_pX264Param->vui.i_sar_height = 720;

	 //* Log
	 m_pX264Param->i_log_level  = X264_LOG_NONE;
	 //* Rate control Parameters
	 m_pX264Param->rc.i_bitrate = 1024;//* 码率(比特率,单位Kbps)
	 m_pX264Param->rc.b_mb_tree = 0;
	 //* muxing parameters
	 m_pX264Param->i_fps_den  = 1; //* 帧率分母
	 m_pX264Param->i_fps_num  = 25;//* 帧率分子
	 m_pX264Param->i_timebase_den = m_pX264Param->i_fps_num;
	 m_pX264Param->i_timebase_num = m_pX264Param->i_fps_den;

	 //* 设置Profile.使用MainProfile
	 x264_param_apply_profile(m_pX264Param, x264_profile_names[2]);

	 //* 打开编码器句柄,通过x264_encoder_parameters得到设置给X264
	  //* 的参数.通过x264_encoder_reconfig更新X264的参数
	  m_pX264Handle = x264_encoder_open(m_pX264Param);
	  assert(m_pX264Handle);

	  //* 获取整个流的PPS和SPS,不需要可以不调用.
	  /*int iResult = x264_encoder_headers(m_pX264Handle, &m_pNals, &m_iNal);
	  assert(iResult >= 0);
	  // PPS SPS 总共只有36B,如何解析出来呢?
	  for (int i = 0; i < m_iNal; ++i)
	  {
	   switch (m_pNals[i].i_type)
	   {
	   case NAL_SPS:
	    break;
	   case  NAL_PPS:
	    break;
	   default:
	    break;
	   }
	  }*/

	  //* 获取允许缓存的最大帧数.
	 int iMaxFrames = x264_encoder_maximum_delayed_frames(m_pX264Handle);
	 iMaxFrames = iMaxFrames;

	  //* 编码需要的参数.
	  m_iNal = 0;
	  m_pNals = NULL;
	  m_pPicIn = new x264_picture_t;
	  m_pPicOut = new x264_picture_t;

	  x264_picture_init(m_pPicOut);
	  x264_picture_alloc(m_pPicIn, X264_CSP_I420, m_pX264Param->i_width, m_pX264Param->i_height);
	  m_pPicIn->img.i_csp = X264_CSP_I420;
	  m_pPicIn->img.i_plane = 3;

	return J_OK;
}

int CLiveParser::Deinit()
{
	//* 清除图像区域
	//x264_picture_clean(m_pPicIn);
	//x264_picture_clean(m_pPicOut);

	x264_encoder_close(m_pX264Handle);
	m_pX264Handle = NULL;

	delete m_pPicIn ;
	m_pPicIn = NULL;

	delete m_pPicOut;
	m_pPicOut = NULL;

	delete m_pX264Param;
	m_pX264Param = NULL;

	if (m_pDataBuff != NULL)
	{
		delete m_pDataBuff;
		m_pDataBuff = NULL;
	}


	return J_OK;
}

int CLiveParser::InputData(const char *pData, int nLen)
{
	WLock(m_rwLocker);
	if (m_dateType == J_VideoMjpeg)
	{
		*((int *)(m_pDataBuff + m_nDataSize)) = nLen;
		m_nDataSize += sizeof(int);
	}
	memcpy(m_pDataBuff + m_nDataSize, pData, nLen);
	m_nDataSize += nLen;
	RWUnlock(m_rwLocker);

	return J_OK;
}

int CLiveParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	WLock(m_rwLocker);
	if (m_dateType == J_VideoMjpeg)
	{
		if (m_nDataSize < (int)sizeof(int))
		{
			streamHeader.dataLen = 0;
			RWUnlock(m_rwLocker);
			return J_NOT_COMPLATE;
		}

		int nOffset = 0;
		int nLen = *((int *)(m_pDataBuff));
		nOffset += sizeof(int);
		memcpy(pData, m_pDataBuff + nOffset, nLen);
		nOffset += nLen;
		memmove(m_pDataBuff, m_pDataBuff + nOffset, m_nDataSize - nOffset);
		m_nDataSize -= nOffset;

		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		streamHeader.dataLen = nLen;
		streamHeader.frameType = J_VideoIFrame;
	}
	else
	{
		int iDataLen = 640 * 480;
		if (m_nDataSize < iDataLen * 2)
		{
			streamHeader.dataLen = 0;
			RWUnlock(m_rwLocker);
			return J_NOT_COMPLATE;
		}

		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		int nOffset = 0;
		YUV422To420((uint8_t *)m_pDataBuff, m_pPicIn->img.plane[0], m_pPicIn->img.plane[1], m_pPicIn->img.plane[2], 640, 480);
		nOffset = iDataLen * 2;

		m_pPicIn->i_pts = 0;//streamHeader.timeStamp * 90;
		//m_pPicIn->i_dts = streamHeader.timeStamp * 90;
		//++g_uiPTSFactor;
		encode(m_pX264Handle, m_pPicIn, m_pPicOut);
		memmove(m_pDataBuff, m_pDataBuff + nOffset, m_nDataSize - nOffset);
		m_nDataSize -= nOffset;

		nOffset = 0;
		for (int i = 0; i < m_iNal; ++i)
		{
			/*static FILE *fp = NULL;
			if (fp == NULL)
				fp = fopen("test.h264", "wb+");
			fwrite(m_pNals[i].p_payload, 1, m_pNals[i].i_payload, fp);*/

			memcpy(pData + nOffset, m_pNals[i].p_payload, m_pNals[i].i_payload);
			nOffset += m_pNals[i].i_payload;
		}

		streamHeader.dataLen = nOffset;
		streamHeader.frameType = J_VideoIFrame;
	}

	RWUnlock(m_rwLocker);
	return J_OK;
}

int CLiveParser::encode(x264_t* pX264Handle, x264_picture_t* pPicIn, x264_picture_t* pPicOut)
{
	 int iResult   = 0;
	 iResult = x264_encoder_encode(pX264Handle, &m_pNals, &m_iNal, pPicIn, pPicOut);
	 if (0 == iResult)
	 {
	  //J_OS::LOGINFO("编码成功,但被缓存了");
	 }
	 else if(iResult < 0)
	 {
		 J_OS::LOGINFO("编码出错");
	 }
	 else if (iResult > 0)
	 {
		 //J_OS::LOGINFO("得到编码数据");
	 }

	 /* {{ 作用不明
	 unsigned char* pNal = NULL;
	 for (int i = 0;i < iNal; ++i)
	 {
	 int iData = 1024 * 32;
	 x264_nal_encode(pX264Handle, pNal,&pNals[i]);
	 }
	 * }} */

	 //* 获取X264中缓冲帧数.
	 int iFrames = x264_encoder_delayed_frames(pX264Handle);
	 //J_OS::LOGINFO("当前编码器中缓存数据: %d", iFrames);
	 return iFrames;
}
