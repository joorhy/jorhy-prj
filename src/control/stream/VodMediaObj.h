#ifndef __VODMEDIAOBJ_H_
#define __VODMEDIAOBJ_H_
#include "j_includes.h"
#include "x_adapter_manager.h"
#include "x_socket.h"

class CVodMediaObj : public J_MediaObj
{
public:
	CVodMediaObj(j_socket_t nSocket, J_Obj *pObj);
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
	j_socket_t m_nSocket;
	j_boolean_t m_bStart;
	j_char_t *m_pDataBuff;
	j_char_t *m_pConvetBuff;
	j_string_t m_resid;

	j_string_t m_fileid;
	j_boolean_t m_bPaused;
	j_char_t *m_pHeader;
	j_boolean_t m_bSendHeader;
	J_StreamHeader m_streamHeader;

	J_OS::CTCPSocket m_sendSocket;
	J_Obj *m_pObj;
	J_FileReader *m_pReader;
	
	j_int64_t m_nextFrameTime;
	j_int64_t m_lastFrameTime;
	j_uint32_t m_lastFrameNum;
};

#endif //~__VODMEDIAOBJ_H_
