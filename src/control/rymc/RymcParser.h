#ifndef __RYMC_PARSER_H_
#define __RYMC_PARSER_H_
#include "x_http_helper.h"
#include "DeviceControl.h"
#include "ModuleManagerDef.h"

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
		virtual int AddUser(int nSocket, const char *pAddr, short nPort);
		virtual	int ProcessRequest(int nSocket, char *&pResponse, int &nRespLen);
		virtual	int DelUser(int nSocket);

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
