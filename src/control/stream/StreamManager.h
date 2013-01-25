#ifndef __STREAMMANAGER_H_
#define __STREAMMANAGER_H_
#include "j_includes.h"
#include "AdapterManager.h"
#include "x_service.h"
#include "x_lock.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"

#include <map>
#include <string>

#define IS_CLOSE_CMD(x)	(J_STOP_REAL == (x) || J_STOP_VOD == (x) || J_STOP_VOICE == (x))

class CStreamManager : public CXService<CStreamManager>
{
	public:
		CStreamManager();
		~CStreamManager();

	public:
		///CXService
		virtual int OnAccept(int nSocket, const char *pAddr, short nPort);
		virtual int OnRead(int nSocket);
		virtual int OnWrite(int nSocket);
		virtual int OnBroken(int nSocket);
		virtual int GetSocketByResid(const char *pResid);

		///CStreamManager
		int StartService(int nPort, const char *pType);
		int StopService();

	private:
		int ParserRequest(int nSocket, J_MediaObj *pClient);
		int ProcessCommand(int nSocket, J_Obj *pObj, J_MediaObj *pClient);
		static void OnMessage(void *user, BaseMessage *pMessage)
		{
			(static_cast<CStreamManager *>(user))->ProcMessage(pMessage);
		}
		void ProcMessage(BaseMessage *pMessage);

	private:
		std::map<int, J_MediaObj *> m_clientMap;			//socket 与 Client对象的映射关系

		typedef std::map<std::string, std::vector<int> >  ResidMap;
		ResidMap m_residMap;
		std::vector<int> m_vecClient;						//存放所有相同Resid请求的socket
		std::string m_serviceType;
};

#endif // ~__STREAMMANAGER_H_
