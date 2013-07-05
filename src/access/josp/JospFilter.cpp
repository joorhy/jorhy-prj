#include "JospFilter.h"
#include "x_string.h"
#include "x_socket.h"
#include "x_mux_factory.h"
#include "x_jo_sdk.h"

const int RATE = 1024;

JO_IMPLEMENT_INTERFACE(Filter, "josp", CJospFilter::Maker)

CJospFilter::CJospFilter()
{
	m_muxFilter = NULL;
	m_nRetLen = 0;
	m_pRetBuff = new char[1024];
	m_state = J_JOSP_HEAD;
	memset(m_strResid, 0, sizeof(m_strResid));
	J_OS::LOGINFO("CJospFilter::CJospFilter()");
}

CJospFilter::~CJospFilter()
{
	if (m_muxFilter)
		JoMuxFactory->DelMux(this);
	
	if (m_pRetBuff)
		delete m_pRetBuff;
	
	J_OS::LOGINFO("CJospFilter::~CJospFilter()");
}

int CJospFilter::Parser(J_AsioDataBase &asioData)
{
	if (m_state == J_JOSP_HEAD)
	{
		J_CtrlHead *pCtrlHead = (J_CtrlHead *)asioData.ioRead.buf;
		switch (pCtrlHead->cmd)
		{
			case jo_open_stream_req:
				m_nCommandType = jo_start_real;
				asioData.ioRead.bufLen = sizeof(J_RealViewData);
				asioData.ioRead.whole = true;
				break;
			case jo_open_file_req:
				m_nCommandType = jo_start_vod;
				m_mode = jo_push_mode;
				asioData.ioRead.bufLen = sizeof(J_VodPlayData);
				asioData.ioRead.whole = true;
				break;
			case jo_req_data_req:
				m_nCommandType = jo_read_data;
				asioData.ioRead.bufLen = sizeof(J_RequestData);
				asioData.ioRead.whole = true;					
				break;
		}
		m_state = J_JOSP_DATA;
		return J_NOT_COMPLATE;
	}
	else if (m_state == J_JOSP_DATA)
	{
		switch (m_nCommandType)
		{
			case jo_start_real:
				{
					J_RealViewData *pRealViewData = (J_RealViewData *)asioData.ioRead.buf;
					m_nStreamType = ntohl(pRealViewData->stream_type);
					memcpy(m_strResid, pRealViewData->res_id, strlen(pRealViewData->res_id));
					
					JoXJoSdk->MakeRespHeader(m_pRetBuff, jo_open_stream_rep, sizeof(J_RealViewRetData));
					J_RealViewRetData *pRetData = (J_RealViewRetData *)(m_pRetBuff + sizeof(J_CtrlHead));
					memcpy(pRetData->media_code, "JOMS", 4);
					pRetData->i_frame_ival = 30;
					pRetData->fps = 25;
					pRetData->width = 1280;
					pRetData->height = 960;
					
					asioData.ioRead.bufLen = sizeof(J_CtrlHead);
					asioData.ioRead.whole = true;
					
					m_nRetLen = sizeof(J_CtrlHead) + sizeof(J_RealViewRetData);
				}
				break;
			case jo_start_vod:
				{
					J_VodPlayData *pVodPlayData = (J_VodPlayData *)asioData.ioRead.buf;
					m_beginTime = ntohl(pVodPlayData->begin_time);
					m_endTime = ntohl(pVodPlayData->end_time);
					memcpy(m_strResid, pVodPlayData->res_id, strlen(pVodPlayData->res_id));
					
					JoXJoSdk->MakeRespHeader(m_pRetBuff, jo_open_file_rep, sizeof(J_VodPlayRetData));
					J_VodPlayRetData *pRetData = (J_VodPlayRetData *)(m_pRetBuff + sizeof(J_CtrlHead));
					memcpy(pRetData->media_code, "JOMS", 4);
					pRetData->i_frame_ival = 30;
					pRetData->fps = 25;
					pRetData->width = 1280;
					pRetData->height = 960;
					
					m_nRetLen = sizeof(J_CtrlHead) + sizeof(J_VodPlayRetData);
				}
				break;
			case jo_read_data:
				{
					J_RequestData *pRequestData = (J_RequestData *)asioData.ioRead.buf;
					m_beginTime = ntohl(pRequestData->begin_time);
					m_endTime = m_beginTime + ntohl(pRequestData->time_ival);
					
					JoXJoSdk->MakeRespHeader(m_pRetBuff, jo_req_data_rep, 0);
					m_nRetLen = 0;
				}		
				break;
		}
		m_state = J_JOSP_HEAD;
	}
	//if (m_nCommandType == jo_start_vod)
	//	return J_WIAT_NEXT_CMD;
		
	m_muxFilter = JoMuxFactory->GetMux(this, "jos");

	return J_OK;
}

const char *CJospFilter::GetResourceType()
{
	if (strstr(m_strResid, ".") != NULL)
		return "jorf";
		
	return "jofs";
}

int CJospFilter::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen)
{
	return m_muxFilter->Convert((const char *)pInputData, streamHeader, pOutputData, nOutLen, (void *)&RATE);
}

int CJospFilter::Complete(J_AsioDataBase &asioData)
{
	j_result_t nResult = J_OK;
	asioData.ioWrite.buf = m_pRetBuff;
	asioData.ioWrite.bufLen = m_nRetLen;
	asioData.ioWrite.whole = true;
	//if (m_nCommandType == jo_start_vod)
	//	nResult = J_WIAT_NEXT_CMD;

	return nResult;
}
