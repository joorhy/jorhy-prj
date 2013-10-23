#ifndef __HIKSDKSTREAM_H_
#define __HIKSDKSTREAM_H_
#include "HikSdkParser.h"
#include "HikSdkParser2.h"
#include "HCNetSDK.h"

class CHikSdkStreamBase : public J_MediaStream
{};

class CHikSdkStream : public J_BaseVideoStream<CHikSdkStreamBase>
{
public:
	CHikSdkStream(j_string_t resid);
	~CHikSdkStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();
	
public:
	static void RealDataCallback(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
	{
		((CHikSdkStream *)pUser)->OnRecvData(lRealHandle, dwDataType, pBuffer, dwBufSize);
	}

private:
	void OnRecvData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);

private:
	j_boolean_t m_bStartup;
	CHikSdkParser2 m_parser;
	char *m_pDataBuff;
	J_OS::TLocker_t m_locker;
};

#endif //~__HIKSDKSTREAM_H_
