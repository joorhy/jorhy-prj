#ifndef __JOSPHELPER_H_
#define __JOSPHELPER_H_

#include "x_socket.h"
#include "j_type.h"

class CJospHelper
{
	public:
		CJospHelper();
		~CJospHelper();
		
	public:
		int OpenStream(J_OS::CTCPSocket *recvSocket, const char *pResid, int nStreamType);
		void CloseStream(J_OS::CTCPSocket *recvSocket, const char *pResid);
		
	private:
		int MakeHeader(char *pBuff, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet = 0x00);
	
	private:
		int m_nSeq;
		int m_nVideoTrackId;
};

#endif //~__JOSPHELPER_H_