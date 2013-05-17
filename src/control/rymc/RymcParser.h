#ifndef __RYMC_PARSER_H_
#define __RYMC_PARSER_H_
#include "x_http_helper.h"
#include "DeviceControl.h"
#include "x_module_manager_def.h"

#define RCD_CONTROL		101
#define RCD_SEARCH_DVR	102
#define PTZ_CONTROL		103
#define RCD_MOVE		104
#define RCD_SEARCH_NVR	105

class CRymcParser : public J_CommandParser
{
	public:
		CRymcParser();
		~CRymcParser();
		
		static int Maker(J_Obj *&pObj)
		{
			pObj = new CRymcParser();
			return J_OK;
		}

	public:
		virtual int AddUser(j_socket_t nSocket, const j_char_t *pAddr, j_int16_t nPort);
		virtual	int ProcessRequest(j_socket_t nSocket, j_char_t *&pResponse, j_int32_t &nRespLen);
		virtual	int DelUser(j_socket_t nSocket);

	private:
		int PtzControl(const char *pResid, int nCmd, int nParam);
		int RecordControl(const char *pResid, int nCmd, int nStreamType);
		int RecordSearch(const char *pResid, time_t beginTime, time_t endTime);

	private:
		CDeviceControl m_deviceControl;
};

PARSER_BEGIN_MAKER(mcsp)
	PARSER_ENTER_MAKER("mcsp", CRymcParser::Maker)
PARSER_END_MAKER()

#endif //~__RYMC_PARSER_H_
