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
};