#ifndef __REALMEDIAOBJ_H_
#define __REALMEDIAOBJ_H_
#include "j_includes.h"
#include "x_adapter_manager.h"
#include "x_socket.h"

class CRealMediaObj : public J_MediaObj
                     , public J_RealMediaObj
{
public:
	CRealMediaObj(int nSocket, int nStreamType, J_Obj *pObj);
	~CRealMediaObj();

public:
	///J_Client
	virtual int Process(int nIoType);
	virtual int Clearn();
	virtual int Run(bool bFlag);
	///J_VideoClient
	virtual const char *GetResid() const;
	
public: 
	int OnWriteData();

private:
	//实时视频
	int StartVideo();
	int StopVideo();

private:
	int m_nSocket;
	int m_nStreamType;
	CRingBuffer *m_pRingBuffer;
	bool m_bStart;
	char *m_pDataBuff;
	char *m_pConvetBuff;

	j_string_t m_resid;

	J_OS::CTCPSocket m_sendSocket;
	J_OS::CTLock m_locker;
	J_StreamHeader m_streamHeader;

	J_Obj *m_pObj;
	int m_taskNum;
};

class CRealTask : public J_Task
{
	public:
		CRealTask() { m_pParam = NULL; }
		~CRealTask() {}
		/// J_Task
		virtual int Run()
		{
			CRealMediaObj *pRealMedia = static_cast<CRealMediaObj *>(m_pParam);
			if (pRealMedia)
				pRealMedia->OnWriteData();
				
			return 0;
		}
};

#endif //~__REALMEDIAOBJ_H_
