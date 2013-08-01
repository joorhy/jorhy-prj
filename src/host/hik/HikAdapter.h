#ifndef __HIKADAPTER_H_
#define __HIKADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_timer.h"
#include "x_socket.h"
#include "x_thread.h"

class CHikAdapterBase : public J_DevAdapter
							 , public J_DevInput
							 , public J_VoiceIcom
{};

class CHikAdapter : public J_BaseAdapter<CHikAdapterBase>
{
	friend class CHikChannel;
	friend class CHikVodStream;
	friend class CHikIntercom;
public:
	CHikAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CHikAdapter();

	static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CHikAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
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
	///J_VoiceAdapter
	virtual int MakeVoice(const char *pResid, J_Obj *&pObj, J_Obj *pOwner, int nChannel);

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
		(static_cast<CHikAdapter *>(pUser))->UserExchange();
	}
	void UserExchange();

#ifdef WIN32
	static unsigned X_JO_API AlarmThread(void *param)
#else
	static void *AlarmThread(void *param)
#endif
	{
		(static_cast<CHikAdapter *>(param))->OnAlarm();

		return 0;
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

	CJoThread m_threadAlarm;
	J_OS::CTCPSocket *m_pAlarmSock;
	j_boolean_t m_bStartAlarm;
};
#endif //~__HIKADAPTER_H_
