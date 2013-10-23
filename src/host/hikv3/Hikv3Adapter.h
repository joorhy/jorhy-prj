#ifndef __HIKADAPTER_H_
#define __HIKADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_timer.h"
#include "x_socket.h"
#include "x_thread.h"

class CHikv3AdapterBase : public J_DevAdapter
							 , public J_DevInput
{};

class CHikv3Adapter  : public J_BaseAdapter<CHikv3AdapterBase>
{
	friend class CHikv3Channel;
	friend class CHikv3VodStream;
public:
	CHikv3Adapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CHikv3Adapter();

	static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CHikv3Adapter(nDrvId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	virtual J_DevStatus GetStatus() const;
	virtual int Broken();
	virtual int MakeChannel(const char *pResid, J_Obj *&pObj, J_Obj *pOwner, int nChannel, int nStream, int nMode);
	///J_AlarmAdapter
	virtual int EnableAlarm();
	virtual int DisableAlarm();
	virtual int EventAlarm(const J_AlarmData &alarmData);

protected:
	int SendCommand(int nCmd, const char *pSendData = NULL, int nDataLen = 0);
	unsigned short CheckSum(unsigned char *addr, int count);
	int GetLocalNetInfo(unsigned long & ipAddr,unsigned char* mac);
	char *GetRemoteIp() const { return (char *)m_remoteIP; }
	int GetRemotePort() const { return m_remotePort; }
	long GetUserId() const { return m_userId; }
	int Relogin();

private:
	int Login();
	int Logout();

	static void OnTimer(void *pUser)
	{
		(static_cast<CHikv3Adapter *>((void *)pUser))->UserExchange();
	}
	void UserExchange();

	static void *AlarmThread(void *param)
	{
		(static_cast<CHikv3Adapter *>(param))->OnAlarm();

		return (void *)0;
	}
	void OnAlarm();

private:
	long m_userId;
	char m_remoteIP[16];
	int  m_remotePort;
	char m_username[64];
	char m_password[64];
	int m_drvId;

	J_DevStatus m_status;
	J_OS::CTimer m_timer;

	pthread_t m_threadAlarm;
	J_OS::CTCPSocket *m_pAlarmSock;
	bool m_bStartAlarm;
};

#endif //~__HIKADAPTER_H_
