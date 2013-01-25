#ifndef __VODMEDIAOBJ_H_
#define __VODMEDIAOBJ_H_
#include "j_includes.h"
#include "AdapterManager.h"
#include "x_socket.h"

class CVodMediaObj : public J_MediaObj
{
public:
	CVodMediaObj(int nSocket, J_Obj *pObj);
	~CVodMediaObj();

public:
	///J_Client
	virtual int Process(int nIoType);
	virtual int Clearn();
	virtual int Run(bool bFlag);

private:
	//NVR回放视频
	int OpenFile();
	int CloseFile();
	int PauseFile();
	int SetTime();
	int SetScale();

private:
	int m_nSocket;
	bool m_bStart;
	char *m_pDataBuff;
	char *m_pConvetBuff;
	std::string m_resid;

	std::string m_fileid;
	bool m_bPaused;
	char *m_pHeader;
	bool m_bSendHeader;
	J_StreamHeader m_streamHeader;

	J_OS::CTCPSocket m_sendSocket;
	J_Obj *m_pObj;
	J_FileReader *m_pReader;
};

#endif //~__VODMEDIAOBJ_H_
