#ifndef __REALMEDIAOBJ_H_
#define __REALMEDIAOBJ_H_
#include "j_includes.h"
#include "x_adapter_manager.h"
#include "x_socket.h"

class CRealMediaObj : public J_MediaObj
                     , public J_RealMediaObj
{
public:
	CRealMediaObj(j_socket_t nSocket, int nStreamType, J_Obj *pObj);
	~CRealMediaObj();

public:
	///J_Client
	virtual int Process(J_AsioDataBase &asioData);
	virtual int Clearn();
	virtual int Run(bool bFlag);
	///J_VideoClient
	virtual const char *GetResid() const;
	
public: 
	int OnWriteData(J_AsioDataBase &asioData);

private:
	//实时视频
	j_result_t StartVideo();
	j_result_t StopVideo();

private:
	j_socket_t m_nSocket;
	j_int32_t m_nStreamType;
	CRingBuffer *m_pRingBuffer;
	j_boolean_t m_bStart;
	j_char_t *m_pDataBuff;
	j_char_t *m_pConvetBuff;

	j_string_t m_resid;

	J_OS::CTCPSocket m_sendSocket;
	J_OS::CTLock m_locker;
	J_StreamHeader m_streamHeader;

	J_Obj *m_pObj;
	j_int32_t m_taskNum;
	j_int64_t m_nextFrameTime;
	j_int64_t m_lastFrameTime;
	j_uint32_t m_lastFrameNum;
};

#endif //~__REALMEDIAOBJ_H_
