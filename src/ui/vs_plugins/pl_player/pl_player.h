// Plugin_3.0.h : main header file for the Plugin_3.0 DLL
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CPlPlayerApp
// See pl_player.cpp for the implementation of this class
//

class CPlPlayerApp : public CWinApp
{
public:
	CPlPlayerApp();

	// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

};

