#ifndef __CONTROLMANAGER_H_
#define __CONTROLMANAGER_H_
#include "j_includes.h"
#include "x_service.h"

#define MAX_READ_SIZE 1024
#define TEST_JO_UI

class CControlManager : public CXService<CControlManager>
{
	public:
		CControlManager();
		~CControlManager();

	public:
		///CXService
		virtual int OnAccept(j_socket_t nSocket, const char *pAddr, short nPort);
		virtual int OnRead(j_socket_t nSocket);
		virtual int OnWrite(j_socket_t nSocket);
		virtual int OnBroken(j_socket_t nSocket);
		virtual j_socket_t GetSocketByResid(const char *pResid){ return j_socket_t(); }

		///CStreamManager
		int StartService(int nPort, const char *pCommandType);
		int StopService();
	private:
		J_CommandParser *m_pCommandParser;
		int m_nPort;
};

#endif //~__CONTROLMANAGER_H_
