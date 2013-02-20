#ifndef __X_RECIVER_H_
#define __X_RECIVER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/socket.h>

struct SocketId_Info
{
	int id;
	int idle; 
};

class CXDecoder;
class CXReciver : public wxEvtHandler
{
	public:
		CXReciver(CXDecoder *decoder);
		~CXReciver();
		
		static SocketId_Info m_idInfo[25];
		static int GetIdleId()
		{
			for (int i=0; i<25; i++)
			{
				if (m_idInfo[i].idle)
				{
					m_idInfo[i].idle = 0;
					return m_idInfo[i].id;
				}
			}
			
			return -1;
		}
		static void SetIdleId(int nId)
		{
			for (int i=0; i<25; i++)
			{
				if (m_idInfo[i].id == nId)
				{
					m_idInfo[i].idle = 1;
					return;
				}
			}
		}
		
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
		CXDecoder *m_pDecoder;
		int m_nSocketId;
};

#endif //~__X_RECIVER_H_