#include "JospFilter.h"
#include "x_string.h"
#include "x_socket.h"
#include "x_mux_factory.h"
#include "x_jo_sdk.h"

const int RATE = 1024;

CJospFilter::CJospFilter()
{
	m_muxFilter = NULL;
	m_nRetLen = 0;
	m_pRetBuff = new char[1024];
	memset(m_strResid, 0, sizeof(m_strResid));
}

CJospFilter::~CJospFilter()
{
	if (m_muxFilter)
		CMuxFactory::Instance()->DelMux(this);
	
	if (m_pRetBuff)
		delete m_pRetBuff;
}

int CJospFilter::Parser(j_socket_t nSocket)
{
	J_OS::CTCPSocket readSocket(nSocket);
	J_CtrlHead ctrlHead = {0};
	int read_ret = readSocket.Read_n((char *)&ctrlHead, sizeof(J_CtrlHead));
	if (read_ret < 0)
		return J_SOCKET_ERROR;
	
	switch (ctrlHead.cmd)
	{
		case jo_open_stream_req:
			{
				J_RealViewData realViewData = {0};
				read_ret = readSocket.Read_n((char *)&realViewData, sizeof(J_RealViewData));
				if (read_ret < 0)
					return J_SOCKET_ERROR;
					
				m_nCommandType = jo_start_real;
				m_nStreamType = ntohl(realViewData.stream_type);
				memcpy(m_strResid, realViewData.res_id, strlen(realViewData.res_id));
				
				CXJoSdk::Instance()->MakeRespHeader(m_pRetBuff, jo_open_stream_rep, sizeof(J_RealViewRetData));
				J_RealViewRetData *pRetData = (J_RealViewRetData *)(m_pRetBuff + sizeof(J_CtrlHead));
				memcpy(pRetData->media_code, "JOMS", 4);
				pRetData->i_frame_ival = 30;
				pRetData->fps = 25;
				pRetData->width = 1280;
				pRetData->height = 960;
				
				m_nRetLen = sizeof(J_CtrlHead) + sizeof(J_RealViewRetData);
			}
			break;
		case jo_open_file_req:
			{
				J_VodPlayData vodPlayData = {0};
				read_ret = readSocket.Read_n((char *)&vodPlayData, sizeof(J_VodPlayData));
				if (read_ret < 0)
					return J_SOCKET_ERROR;
					
				m_nCommandType = jo_start_vod;
				m_mode = jo_push_mode;
				m_beginTime = ntohl(vodPlayData.begin_time);
				m_endTime = ntohl(vodPlayData.end_time);
				memcpy(m_strResid, vodPlayData.res_id, strlen(vodPlayData.res_id));
				
				CXJoSdk::Instance()->MakeRespHeader(m_pRetBuff, jo_open_file_rep, sizeof(J_VodPlayRetData));
				J_VodPlayRetData *pRetData = (J_VodPlayRetData *)(m_pRetBuff + sizeof(J_CtrlHead));
				memcpy(pRetData->media_code, "JOMS", 4);
				pRetData->i_frame_ival = 30;
				pRetData->fps = 25;
				pRetData->width = 1280;
				pRetData->height = 960;
				
				m_nRetLen = sizeof(J_CtrlHead) + sizeof(J_VodPlayRetData);
			}
			break;
		case jo_req_data_req:
			{
				J_RequestData requestData = {0};
				read_ret = readSocket.Read_n((char *)&requestData, sizeof(J_RequestData));
				if (read_ret < 0)
					return J_SOCKET_ERROR;
					
				m_nCommandType = jo_read_data;
				m_beginTime = ntohl(requestData.begin_time);
				m_endTime = m_beginTime + ntohl(requestData.time_ival);
				
				CXJoSdk::Instance()->MakeRespHeader(m_pRetBuff, jo_req_data_rep, 0);
				m_nRetLen = 0;//sizeof(J_CtrlHead);
			}
			break;
	}

	m_muxFilter = CMuxFactory::Instance()->GetMux(this, "jos");

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

int CJospFilter::Complete(j_socket_t nSocket)
{
	J_OS::CTCPSocket writeSocket(nSocket);
	if (writeSocket.Write_n((char *)m_pRetBuff, m_nRetLen) < 0)
	{
		J_OS::LOGERROR("CJospFilter::Complete Send Header error");
		return J_SOCKET_ERROR;
	}

	return J_OK;
}
