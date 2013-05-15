#ifndef __VODMEDIAOBJ_H_
#define __VODMEDIAOBJ_H_
#include "j_includes.h"
#include "x_adapter_manager.h"
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
	int ReadData();
	int WriteData();

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
	
	j_int64_t m_nextFrameTime;
	j_int64_t m_lastFrameTime;
	j_uint32_t m_lastFrameNum;
};

#endif //~__VODMEDIAOBJ_H_
