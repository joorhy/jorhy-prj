#ifndef __JORFILEHELPER_H_
#define __JORFILEHELPER_H_

#include "x_socket.h"
#include "j_type.h"

class CJorFileHelper
{
	public:
		CJorFileHelper();
		~CJorFileHelper();
		
	public:
		int OpenFile(J_OS::CTCPSocket *recvSocket, const char *pResid, j_time_t begin, j_time_t end);
		void CloseFile(J_OS::CTCPSocket *recvSocket, const char *pResid);
		int ReadFile(J_OS::CTCPSocket *recvSocket, const char *pResid, j_time_t begin, int nIval);
		
	private:
};

#endif //~__JORFILEHELPER_H_