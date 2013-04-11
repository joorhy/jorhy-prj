#pragma once
#include "pl_core.h"
#include "pl_player.h"
#include "pl_singleton.h"

class PL_API PlJsonParser : public SingletonTmpl<PlJsonParser>
{
public:
	PlJsonParser();
	~PlJsonParser();

public:
	BOOL ParserLayout(const char *pJsStr, PL_LayoutInfo &layoutInfo);
	BOOL ParserLayout2(const char *pJsStr, PL_LayoutInfo &layoutInfo);
	BOOL ParserPlay(const char *pJsStr, PL_PlayInfo &playInfo);
	BOOL ParserDrag(const char *pJsStr, PL_PlayInfo &playInfo);
	BOOL MakeWndParam(const PL_PlayInfo &playInfo, char *pJsStr);
	BOOL MakeAllWndParam(char **pVecStr, int nWndNum, char *pJsStr);
	BOOL MakeCbStatus(const PL_PlayInfo &playInfo, char *pJsStr);
	BOOL MakeFocus(const PL_PlayInfo &playInfo, char *pJsStr);
};