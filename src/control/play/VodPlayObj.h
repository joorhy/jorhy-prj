#ifndef __VODPLAYOBJ_H_
#define __VODPLAYOBJ_H_
#include "j_includes.h"

class CVodPlayObj : public J_PlayerObj
{
public:
	CVodPlayObj(int nStreamId, const char *pPlayerType, const char *pReaderType, const char *pResid);
	~CVodPlayObj();

public:
	///J_PlayerObj
	virtual j_result_t PlayVod(j_wnd_t hWnd, j_uint64_t nStart, j_uint64_t nEnd);
	virtual j_result_t StopVod();
	virtual j_result_t ProcessMedia();
	virtual j_result_t AspectRatio(j_int32_t nWidth, j_int32_t nHeight);

private:
	//NVR»Ø·ÅÊÓÆµ
	int OpenFile(j_uint64_t nStart, j_uint64_t nEnd);
	int CloseFile();

private:
	j_socket_t m_nSocket;
	j_boolean_t m_bStart;
	j_string_t m_readerType;
	j_string_t m_resid;
	j_string_t m_fileid;
	j_string_t m_playerType;

	J_StreamHeader m_streamHeader;
	j_int32_t m_mode;
	J_FileReader *m_pReader;

	j_char_t *m_pDataBuff;
	//j_char_t *m_pConvetBuff;
	j_int64_t m_nextFrameTime;
	j_int64_t m_lastFrameTime;
	j_uint32_t m_lastFrameNum;
};
#endif //~__VODPLAYOBJ_H_