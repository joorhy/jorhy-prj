#ifndef __RYMC_PARSER_H_
#define __RYMC_PARSER_H_
#include "j_includes.h"
#include "x_http_helper.h"
#include "DeviceControl.h"
#include "x_module_manager_def.h"

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
		virtual	int ProcessRequest(J_AsioDataBase *pAsioData_in, J_AsioDataBase *pAsioData_out);
		virtual	int DelUser(j_socket_t nSocket);

	private:
		int PtzControl(const char *pResid, int nCmd, int nParam);
		int RecordControl(const char *pResid, int nCmd, int nStreamType);
		int RecordSearch(const char *pResid, j_time_t beginTime, j_time_t endTime, json_object **json_param_obj);
		int GetRecordInfo(const char *pResid, json_object **json_param_obj);
		int GetRecordResid(json_object **json_param_obj);
		int DelRecord(J_DelRecordCtrl &delRecordCtrl);

	private:
		enum
		{
			RYMC_HEAD,
			RYMC_BODY,
			RYMC_FINISH,
		};
		CDeviceControl m_deviceControl;
		j_char_t m_read_buff[2048];
		j_int32_t m_read_len;
		j_int32_t m_state;
};

#endif //~__RYMC_PARSER_H_
