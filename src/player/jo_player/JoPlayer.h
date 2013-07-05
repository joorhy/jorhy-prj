#ifndef __JOPLAYER_H_
#define __JOPLAYER_H_
#include "j_includes.h"

class CJoPlayer : public J_Player
{
public:
	CJoPlayer();
	~CJoPlayer();

public:
	///J_Player
	virtual j_result_t Play(j_wnd_t hWnd);
	virtual j_result_t Stop();
	virtual j_result_t InputData(j_char_t *pData, j_int32_t nLen);
};

#endif //~__JOPLAYER_H_