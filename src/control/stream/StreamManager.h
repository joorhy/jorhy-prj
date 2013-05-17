#ifndef __STREAMMANAGER_H_
#define __STREAMMANAGER_H_
#include "j_includes.h"
#include "x_adapter_manager.h"
#include "x_service.h"
#include "x_lock.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"

#include <map>
#include <string>

#define IS_CLOSE_CMD(x)	(jo_stop_real == (x) || jo_stop_vod == (x) || jo_stop_voice == (x))

class CStreamManager : public CXService<CStreamManager>
{
	public:
		CStreamManager();
		~CStreamManager();

	public:
		///CXService
		virtual int OnAccept(j_socket_t nSocket, const char *pAddr, short nPort);
		virtual int OnRead(j_socket_t nSocket);
		virtual int OnWrite(j_socket_t nSocket);
		virtual int OnBroken(j_socket_t nSocket);
		virtual j_socket_t GetSocketByResid(const char *pResid);

		///CStreamManager
		int StartService(int nPort, const char *pType);
		int StopService();

	private:
		int ParserRequest(j_socket_t nSocket, J_MediaObj *pClient);
		int ProcessCommand(j_socket_t nSocket, J_Obj *pObj, J_MediaObj *pClient);
		static void OnMessage(void *user, BaseMessage *pMessage)
		{
			(static_cast<CStreamManager *>(user))->ProcMessage(pMessage);
		}
		void ProcMessage(BaseMessage *pMessage);

	private:
		std::map<j_socket_t, J_MediaObj *> m_clientMap;			//socket 与 Client对象的映射关系

		typedef std::map<std::string, std::vector<j_socket_t> >  ResidMap;
		ResidMap m_residMap;
		std::vector<j_socket_t> m_vecClient;						//存放所有相同Resid请求的socket
		std::string m_serviceType;
};

#endif // ~__STREAMMANAGER_H_
