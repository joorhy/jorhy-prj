#include "StdAfx.h"
#include "pl_ctrl.h"
#include "pl_type.h"
#include "pl_factory.h"
#include "pl_factory_wnd.h"
#include "pl_json_parser.h"
#include "pl_wnd.h"
#include <cmath>
using namespace std;

CPlCtrl::CPlCtrl(void)
{
	m_hParent	= NULL;
	m_pUser		= NULL;
}

CPlCtrl::~CPlCtrl(void)
{
	int size = m_vecPlayWnd.size();
	for(int i=size; i>0; --i)
	{
		CPlFactoryWnd::Instance()->DelWindow(i);
	}
	m_vecPlayWnd.clear();
}

BOOL CPlCtrl::InitDisPlay(HWND hParent, char* pJsUrl)
{
	if(m_hParent != NULL)
		return TRUE;

	if (!PlJsonParser::Instance()->ParserLayout(pJsUrl, m_layoutInfo))
		return FALSE;

	int nWindows = FindShowWndNum();
	switch(m_layoutInfo.nMod)
	{
	case STREAME_REALTIME:		//real
		for(int i=0; i<nWindows; ++i)
		{
			CPlWnd *r_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("r_play", hParent, i+1));
			m_vecPlayWnd.push_back(r_tmp);
		}
		break;
	case STREAME_FILE:		//vod
		for(int i=0; i<nWindows; ++i)
		{
			CPlWnd *v_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("v_play", hParent, i+1));
			m_vecPlayWnd.push_back(v_tmp);
		}
		break;
	default:
		return FALSE;
	}
	m_hParent = hParent;
	SetLayout(m_layoutInfo);
	SetAllUserData();
	return TRUE;
}

int CPlCtrl::FindShowWndNum()
{
	return FindShowWndNum(m_layoutInfo);
}

int CPlCtrl::FindShowWndNum(const PL_LayoutInfo &layoutInfo)
{
	int nWndNum = 1;
	if(3 == layoutInfo.nLayout)
	{
		nWndNum = (layoutInfo.nWindows + 1) * (layoutInfo.nWindows + 1);
	}
	return nWndNum;
}

BOOL CPlCtrl::SetLayout(char *pJsUrl)
{
	PL_LayoutInfo layoutInfo;
	if (!PlJsonParser::Instance()->ParserLayout(pJsUrl, layoutInfo))
		return FALSE;

	if(SetLayout(layoutInfo))
	{
		m_layoutInfo.nLayout = layoutInfo.nLayout;
		m_layoutInfo.nWindows = layoutInfo.nWindows;
		m_layoutInfo.nMax = layoutInfo.nMax;
		return TRUE;
	}
	return FALSE;
}

BOOL CPlCtrl::SetLayout(const PL_LayoutInfo &layoutInfo)
{
	int nOldNum = m_vecPlayWnd.size();
	int nDisplayNum = FindShowWndNum();
	int nNewNum = FindShowWndNum(layoutInfo);
	if(nOldNum < nNewNum)
	{
		switch(m_layoutInfo.nMod)
		{
		case STREAME_REALTIME:		//real
			for(int i=nOldNum; i<nNewNum; ++i)
			{
				CPlWnd *r_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i+1));
				m_vecPlayWnd.push_back(r_tmp);
			}
			break;
		case STREAME_FILE:		//vod
			for(int i=nOldNum; i<nNewNum; ++i)
			{
				CPlWnd *v_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("v_play", m_hParent, i+1));
				m_vecPlayWnd.push_back(v_tmp);
			}
			break;
		}
	}
	CRect rect;
	GetClientRect(m_hParent, &rect);
	ShowAllowWindow(nNewNum, nDisplayNum);
	switch(layoutInfo.nLayout)
	{
	case 1:
		for(int i=0; i<nNewNum; ++i)
		{
			((CWnd*)m_vecPlayWnd[i])->MoveWindow(rect.left+i*rect.Width() / nNewNum,
										rect.top,
										rect.Width() / nNewNum,					
										rect.Height());
		}
		break;
	case 2:
		for(int i=0; i<nNewNum; i++)
		{
			((CWnd*)m_vecPlayWnd[i])->MoveWindow(rect.left,		
										rect.top+i*rect.Height() / nNewNum,
										rect.Width(),	
										rect.Height() / nNewNum);
		}
		break;
	case 3:
		switch(layoutInfo.nWindows)
		{
		case SF_ONE:
			GridWindow(1);
			break;
		case SF_FOUR:
			GridWindow(4);
			break;
		case SF_NINE:
			GridWindow(9);
			break;
		case SF_SIXTEEN:
			GridWindow(16);
			break;
		}
		break;
	default:
		return FALSE;
	}
	SetAllFullModel(layoutInfo.nMax);
	m_vecPlayWnd[0]->SetNowShowWindow(nNewNum);
	::SendMessage(GetFocusWnd(), WM_OWN_SETFOCUS, 0, 0);
	return TRUE;
}

void CPlCtrl::GridWindow(int nWndNum)
{
	CRect rect;
	GetClientRect(m_hParent,&rect);
	int nNum = sqrt((double)nWndNum);
	for(int i=0; i<nNum; ++i)
		{
			for(int j=0; j<nNum; ++j)
			{
				((CWnd*)m_vecPlayWnd[i*nNum+j])->MoveWindow(rect.left + j*rect.Width() / nNum,
												rect.top + i*rect.Height() / nNum,
												rect.Width() / nNum,
												rect.Height() / nNum);
			}
		}
}

void CPlCtrl::SetAllFullModel(UINT nType)
{
	int size = m_vecPlayWnd.size();
	for(int i=0; i<size; ++i)
	{
		m_vecPlayWnd[i]->SetFullModel(nType);
	}
}

HWND CPlCtrl::GetFocusWnd()
{
	return m_vecPlayWnd[0]->GetFocusWnd(); 
}

void CPlCtrl::ShowAllowWindow(int nNewNum,int nOldNum)
{
	if(nNewNum < nOldNum)
	{
		for(int i=nNewNum; i<nOldNum; ++i)
		{
			::ShowWindow(((CWnd*)m_vecPlayWnd[i])->m_hWnd, SW_HIDE);
		}
	}
	else if(nOldNum < nNewNum)
	{
		for(int i=nOldNum; i<nNewNum; ++i)
		{
			::ShowWindow(((CWnd*)m_vecPlayWnd[i])->m_hWnd, SW_SHOW);
		}
	}
}

BOOL CPlCtrl::RegisterCallBack(NpnNotifyFunc funcAddr, void *pUser)
{
	m_pUser = pUser;
	return PlManager::Instance()->RegisterCallBack(funcAddr);
}

BOOL CPlCtrl::StopAll()
{
	int nSize = m_vecPlayWnd.size();
	for(int i=0; i<nSize; ++i)
	{
		PlManager::Instance()->Stop(((CWnd*)m_vecPlayWnd[i])->m_hWnd);
	}
	return TRUE;
}

BOOL CPlCtrl::VodStreamJump(char *js_time)
{
	if(m_layoutInfo.nMod == STREAME_REALTIME) 
		return FALSE;

	PL_PlayInfo playInfo = {0};
	PlJsonParser::Instance()->ParserPlay(js_time, playInfo);

	return PlManager::Instance()->VodStreamJump(GetFocusWnd(), playInfo);
}

BOOL CPlCtrl::GetPath(char *psz_dest,UINT nType)
{
	if(nType == IMAGEPATH)
	{
		strncpy(psz_dest, m_layoutInfo.imgPath, PATH_LENGTH);
	}
	else if(nType == VIDEOPATH)
	{
		strncpy(psz_dest, m_layoutInfo.mediaPath, PATH_LENGTH);
	}

	return TRUE;
}

BOOL CPlCtrl::SetLayout()
{
	if(m_layoutInfo.nLayout == -1) 
		return FALSE;

	return SetLayout(m_layoutInfo);
}

BOOL CPlCtrl::Play(char *js_mrl)
{
	BOOL bRet = FALSE;
	HWND hWnd = NULL;
	PL_PlayInfo playInfo = {0};
	PlJsonParser::Instance()->ParserPlay(js_mrl, playInfo);
	if(0 == playInfo.nId)
	{
		hWnd = GetNextPlayWnd();
	}
	else
	{
		int nSize = m_vecPlayWnd.size();
		if(playInfo.nId > nSize || playInfo.nId < 0) 
			return FALSE;

		hWnd = m_vecPlayWnd[playInfo.nId]->m_hWnd;
	}
	bRet = PlManager::Instance()->Play(hWnd, playInfo);

	return bRet;
}

HWND CPlCtrl::GetNextPlayWnd()
{
	int nWndNum = FindShowWndNum();
	for(int i=0; i<nWndNum; ++i)
	{
		if(!PlManager::Instance()->IsPlaying(m_vecPlayWnd[i]->m_hWnd))
		{
			return m_vecPlayWnd[i]->m_hWnd;
		}
	}
	//return ((CPlayWnd*)m_vctPlayWnd[0])->m_hWnd;
	return GetFocusWnd();
}

BOOL CPlCtrl::GetWndParm(char *pRet, int nType)
{
	BOOL bRet = FALSE;
	char wndinfo[2048] = {0};
	if(nType == FOCUS_WINDOW)
	{
		int nId = GetWindowLong(GetFocusWnd(), GWL_ID);
		bRet = PlManager::Instance()->GetWndPlayParm(m_vecPlayWnd[nId-1]->m_hWnd, wndinfo);
	}
	else if(nType == ALL_WINDOW)
	{
		char ppWndInfo[64][64];
		int nWndNum = m_vecPlayWnd.size();
		int nRealNum = 0;
		for (int i=0; i<nWndNum; ++i)
		{
			memset(ppWndInfo[i], 0, 64);
			bRet = PlManager::Instance()->GetWndPlayParm(m_vecPlayWnd[i]->m_hWnd, ppWndInfo[i]);
			if (bRet)
			{
				++nRealNum;
			}
		}
		PlJsonParser::Instance()->MakeAllWndParam((char **)ppWndInfo, nRealNum, wndinfo);
	}
	strcat(pRet, wndinfo);

	return bRet;
}

BOOL CPlCtrl::SetAllUserData()
{
	int nWndNum = FindShowWndNum();
	if(!m_pUser)
		return FALSE;
	for(int i=0; i<nWndNum; ++i)
	{
		if(!PlManager::Instance()->SetUserData(m_vecPlayWnd[i]->m_hWnd, m_pUser))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CPlCtrl::SleepPlayer(bool bSleep)
{
	int nWndNum = FindShowWndNum();
	for(int i=0; i<nWndNum; ++i)
	{
		PlManager::Instance()->SleepPlayer(m_vecPlayWnd[i]->m_hWnd, bSleep);
	}
}