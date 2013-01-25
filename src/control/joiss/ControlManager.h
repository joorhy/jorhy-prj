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
		virtual int OnAccept(int nSocket, const char *pAddr, short nPort);
		virtual int OnRead(int nSocket);
		virtual int OnWrite(int nSocket);
		virtual int OnBroken(int nSocket);
		virtual int GetSocketByResid(const char *pResid){ return 0; }

		///CStreamManager
		int StartService(int nPort, const char *pCommandType);
		int StopService();
	private:
		J_CommandParser *m_pCommandParser;
		int m_nPort;
};

#endif //~__CONTROLMANAGER_H_
