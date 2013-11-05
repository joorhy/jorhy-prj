#ifndef __JOPLAYER_H_
#define __JOPLAYER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_thread.h"

class CJoPlayer : public J_Player
{
public:
	CJoPlayer();
	~CJoPlayer();

	static j_result_t Maker(J_Obj *&pObj)
	{
		pObj = new CJoPlayer();
		return J_OK;
	}

public:
	///J_Player
	virtual j_result_t Play(j_wnd_t hWnd);
	virtual j_result_t Stop();
	virtual j_result_t InputData(j_char_t *pData, J_StreamHeader &streamHeader);
	virtual j_result_t AspectRatio(j_int32_t nWidth, j_int32_t nHeight);

private:
	j_result_t Init();
	void Deinit();

#ifdef WIN32
	static unsigned X_JO_API DecodeThread(void *param)
#else
	static void *DecodeThread(void *param)
#endif
	{
		(static_cast<CJoPlayer *>(param))->OnDecode();
		return 0;
	}
	void OnDecode();

#ifdef WIN32
	static unsigned X_JO_API RendThread(void *param)
#else
	static void *RendThread(void *param)
#endif
	{
		(static_cast<CJoPlayer *>(param))->OnRend();
		return 0;
	}
	void OnRend();

private:
	J_Decoder *m_decoder;
	J_Render *m_render;
	j_boolean_t m_bInitRender;
	j_wnd_t m_hwnd;
	CRingBuffer *m_rawBuffer;
	CRingBuffer *m_vBuffer;
	CRingBuffer *m_vBuffer2;

	j_boolean_t m_bStart;
	CJoThread m_decThread;
	CJoThread m_rendThread;
	J_OS::CTLock m_lockerDec;
	J_OS::CTLock m_lockerRend;
	J_OS::CXSem m_semDec;
	J_OS::CXSem m_semRend;
	j_int32_t m_width;
	j_int32_t m_height;
};

#endif //~__JOPLAYER_H_