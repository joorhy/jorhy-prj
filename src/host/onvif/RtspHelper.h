#ifndef __RTSPHELPER_H_
#define __RTSPHELPER_H_

#include "x_socket.h"

class CRtspHelper
{
	public:
		CRtspHelper();
		~CRtspHelper();
		
	public:
		int OpenStream(J_OS::CTCPSocket *m_recvSocket, const char *pAddr, int nPort, int nChannel);
		void CloseStream(J_OS::CTCPSocket *m_recvSocket, const char *pAddr, int nPort, int nChannel);
		
	private:
		bool IsSeccess(const char *pResp);
		int ParserSDP(const char *pSDP);
	
	private:
		int m_nSeq;
		int m_nVideoTrackId;
};

#endif //~__RTSPHELPER_H_