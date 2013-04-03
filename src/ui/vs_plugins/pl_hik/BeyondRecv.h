#pragma once

#include "BeyondSocket.h"
#include "BeyondBuffer.h"
#include <process.h>
class BeyondRecv
{
public:
	BeyondRecv(void);
	~BeyondRecv(void);

public:
	BOOL StartRecv(char *psz_mrl,BeyondBuffer *pBuff);
	BOOL StopRecv();
	BOOL PauseRecv(BOOL bPause);
	BOOL SetSpeedRecv(BOOL bSpeed);
	BOOL VodJumpRecv(char *pNewMrl);

private:
	BOOL GetAddr(char *OUT_ip,int &OUT_port,char *IN_mrl);
	BOOL MakeHttpRequst(char *OUT_request,char *IN_mrl);
	static DWORD WINAPI RecvThread(void *param);
	void RecvData();

private:
	BeyondSocket *m_socket;
	BeyondBuffer *m_pBuff;
	BOOL m_bStart;
	BOOL m_bPause;
	HANDLE m_hPauseEvent;
};
