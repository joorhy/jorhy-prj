#ifndef __X_RECIVER_H_
#define __X_RECIVER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/socket.h>

class CXDecoder;
class CXReciver : public wxEvtHandler
{
	public:
		CXReciver(CXDecoder *decoder);
		~CXReciver();
		
	public:
		int Connect(const char *pAddr, int nPort);
		void Disconnect();
		int StartView(const char *pResid, int nStreamType);
		void StopView();
		
	private:
		void OnSocketEvent(wxSocketEvent& event);
        DECLARE_EVENT_TABLE()
		int MakeHeader(char *pBuff, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet = 0x00);

	private:
		CXReciver *m_pThis;
		wxSocketClient *m_sock;
		char *m_pRecvBuff;
		bool m_bRun;
		CXDecoder *m_pDecoder;
};

#endif //~__X_RECIVER_H_