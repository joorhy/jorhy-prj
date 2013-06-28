#ifndef __STREAMMANAGER_H_
#define __STREAMMANAGER_H_
#include "j_includes.h"
#include "x_adapter_manager.h"
#include "x_lock.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"
#include "x_asio.h"

#include <map>
#include <string>

#define IS_CLOSE_CMD(x)	(jo_stop_real == (x) || jo_stop_vod == (x) || jo_stop_voice == (x))

class JO_API CStreamManager : public J_AsioUser
{
	public:
		CStreamManager();
		~CStreamManager();

	public:
		///AsioUser
		virtual void OnAccept(const J_AsioDataBase *pAsioData, int nRet);
		virtual void OnRead(const J_AsioDataBase *pAsioData, int nRet);
		virtual void OnWrite(const J_AsioDataBase *pAsioData, int nRet);
		virtual void OnBroken(const J_AsioDataBase *pAsioData, int nRet);

		///CStreamManager
		int StartService(int nPort, const char *pType);
		int StopService();

	private:
		int ParserRequest(const J_AsioDataBase *pAsioData, J_MediaObj *pClient);
		int ProcessCommand(const J_AsioDataBase *pAsioData, J_Obj *pObj, J_MediaObj *pClient);

private:
	struct ClientInfo
	{
		J_AsioDataBase *pAsioData;
		J_MediaObj *pObj;
	};
	typedef std::map<j_asio_handle, ClientInfo> ClientMap;
	ClientMap m_clientMap;			//socket 与 Client对象的映射关系

	typedef std::map<std::string, std::vector<j_socket_t> >  ResidMap;
	ResidMap m_residMap;
	std::vector<j_socket_t> m_vecClient;						//存放所有相同Resid请求的socket
	j_string_t m_serviceType;
	j_socket_t m_socket;
	J_AsioDataBase m_asioData;
	CRdAsio m_asio;
};

#endif // ~__STREAMMANAGER_H_
