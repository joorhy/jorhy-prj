#include "StdAfx.h"
#include "pl_ctrl.h"
#include "pl_type.h"
#include "pl_factory.h"
#include "pl_factory_wnd.h"
#include "pl_json_parser.h"
#include "pl_wnd.h"
#include <cmath>
using namespace std;

//std::map<HWND, CPlCtrl*>	CPlCtrl::m_ctrlMap;
//PlLock	CPlCtrl::m_lock;
//int CPlCtrl::m_nIndex		= 0;

//CPlCtrl *CPlCtrl::CreateInstance(HWND pWnd)
//{
//	m_lock.Lock();
//	CPlCtrl *pCtrl = NULL;
//	std::map<HWND, CPlCtrl*>::iterator it = m_ctrlMap.find(pWnd);
//	if (it == m_ctrlMap.end())
//	{
//		pCtrl = new CPlCtrl();
//		m_ctrlMap[pWnd] = pCtrl;
//	}
//	else
//		pCtrl = it->second;
//	m_lock.Unlock();
//
//	return pCtrl;
//}
//
//void CPlCtrl::ReleaseInstance(HWND pWnd)
//{
//	m_lock.Lock();
//	CPlCtrl *pCtrl = NULL;
//	std::map<HWND, CPlCtrl*>::iterator it = m_ctrlMap.find(pWnd);
//	if (it != m_ctrlMap.end())
//	{
//		delete  it->second;
//		m_ctrlMap.erase(it);
//	}
//	m_lock.Unlock();
//	PlManager::Destroy();
//}

CPlCtrl::CPlCtrl(void)
{
	m_hParent	= NULL;
	m_pUser		= NULL;
	memset(&m_layoutInfo, 0, sizeof(PL_LayoutInfo));

	//AllocConsole();
	//SetConsoleTitle("BTKPlayer-Debug");
	//freopen("CONOUT$", "w", stderr);
	//freopen("CONOUT$", "w", stdout);
}

CPlCtrl::~CPlCtrl(void)
{
	m_layoutInfo.bInit = FALSE;
	StopAll();
	DestroyWindows();
}

BOOL CPlCtrl::InitDisPlay(HWND hParent, char* pJsUrl)
{
	if(m_hParent != NULL)
		return TRUE;

	//m_key.hWnd = hParent;
	if (!PlJsonParser::Instance()->ParserLayout(pJsUrl, m_layoutInfo))
		return FALSE;

	m_hParent = hParent;
	CreateWindows(m_layoutInfo);
	m_layoutInfo.bInit = TRUE;
	SetLayout(m_layoutInfo);
	
	return TRUE;
}

int CPlCtrl::CalcWndNum(const PL_LayoutInfo &layoutInfo)
{
	int nWndNum = (layoutInfo.nWindows + 1);
	if(2 == layoutInfo.nLayout)
	{
		nWndNum -= 1;
	}
	else if(3 == layoutInfo.nLayout)
	{
		nWndNum *= nWndNum;
	}
	return nWndNum;
}

BOOL CPlCtrl::SetLayout(char *pJsUrl)
{
	PL_LayoutInfo layoutInfo;
	if (!PlJsonParser::Instance()->ParserLayout2(pJsUrl, layoutInfo))
		return FALSE;
	
	CreateWindows(layoutInfo);
	if(SetLayout(layoutInfo))
	{
		m_layoutInfo.nLayout = layoutInfo.nLayout;
		m_layoutInfo.nWindows = layoutInfo.nWindows;
		m_layoutInfo.nMax = layoutInfo.nMax;
		return TRUE;
	}
	return FALSE;
}

BOOL CPlCtrl::SetPath(char *js_path)
{
	if (PlJsonParser::Instance()->ParserPath(js_path, m_layoutInfo))
	{
		PlManager::Instance()->SetPath(m_layoutInfo.imgPath, m_layoutInfo.mediaPath);
		return TRUE;
	}

	return FALSE;
}

BOOL CPlCtrl::SetLayout(const PL_LayoutInfo &layoutInfo)
{
	//WindowKey key = {m_hParent, 0};
	int nWindowNum = CalcWndNum(layoutInfo);
	CRect rect;
	GetClientRect(m_hParent, &rect);
	switch(layoutInfo.nLayout)
	{
	case 1:
		for(int i=0; i<nWindowNum; ++i)
		{
			//m_key.nId = i + (UINT)m_hParent;
			((CWnd*)m_playWndMap[i])->MoveWindow(rect.left+i*rect.Width() / nWindowNum,
										rect.top,
										rect.Width() / nWindowNum,					
										rect.Height());
		}
		break;
	case 2:
		for(int i=0; i<nWindowNum; ++i)
		{
			//m_key.nId = i + (UINT)m_hParent;
			((CWnd*)m_playWndMap[i])->MoveWindow(rect.left,		
										rect.top+i*rect.Height() / nWindowNum,
										rect.Width(),	
										rect.Height() / nWindowNum);
		}
		break;
	case 3:
		GridWindow(layoutInfo.nWindows+1);
		break;
	}
	//m_key.nId = 0 + (UINT)m_hParent;
	m_playWndMap[0]->SetNowShowWindow(nWindowNum);
	return TRUE;
}

void CPlCtrl::GridWindow(int nWndNum)
{
	//WindowKey key = {m_hParent, 0};
	CRect rect;
	GetClientRect(m_hParent,&rect);
	for(int i=0; i<nWndNum; ++i)
	{
		for(int j=0; j<nWndNum; ++j)
		{
			//m_key.nId = i*nWndNum+j + (UINT)m_hParent;
			((CWnd*)m_playWndMap[i*nWndNum+j])->MoveWindow(rect.left + j*rect.Width() / nWndNum,
											rect.top + i*rect.Height() / nWndNum,
											rect.Width() / nWndNum,
											rect.Height() / nWndNum);
			((CWnd*)m_playWndMap[i*nWndNum+j])->Invalidate(TRUE);
		}
	}
	int nTotleWindow = m_playWndMap.size();
	int m = nWndNum * nWndNum;
	//WINDOWPLACEMENT placement;
	//BOOL dwError;
	for (; m < nTotleWindow; ++m)
	{
		::ShowWindow(m_playWndMap[m]->m_hWnd, SW_HIDE);
		//dwError = IsWindowVisible(m_playWndMap[m]->m_hWnd);
		/*::GetWindowPlacement(m_playWndMap[m]->m_hWnd, &placement);
		placement.showCmd = SW_HIDE;
		if (::SetWindowPlacement(m_playWndMap[m]->m_hWnd, &placement) == 0)
			dwError = GetLastError();
		::GetWindowPlacement(m_playWndMap[m]->m_hWnd, &placement);*/
	}
}

HWND CPlCtrl::GetFocusWnd()
{
	//WindowKey key = {m_hParent, 0};
	//m_key.nId = 0 + (UINT)m_hParent;
	return m_playWndMap[0]->GetFocusWnd(); 
}

BOOL CPlCtrl::RegisterCallBack(NpnNotifyFunc funcAddr, void *pUser)
{
	m_pUser = pUser;
	return PlManager::Instance()->RegisterCallBack(funcAddr);
}

BOOL CPlCtrl::StopAll()
{
	PlayWndMap::iterator it = m_playWndMap.begin();
	for(; it!=m_playWndMap.end(); ++it)
		PlManager::Instance()->Stop(it->second->m_hWnd);

	return TRUE;
}

BOOL CPlCtrl::VodStreamJump(char *js_time)
{
	if(m_layoutInfo.nMod == STREAME_REALTIME) 
		return FALSE;

	PL_PlayInfo playInfo = {0};
	PlJsonParser::Instance()->ParserDrag(js_time, playInfo);

	return PlManager::Instance()->VodStreamJump(GetFocusWnd(), playInfo);
}

BOOL CPlCtrl::SetLayout()
{
	if(!m_layoutInfo.nLayout) 
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
		int nSize = m_playWndMap.size();
		if(playInfo.nId > nSize || playInfo.nId < 0) 
		{
			//printf("%d > %d\n", playInfo.nId, nSize);
			return FALSE;
		}

		//WindowKey key = {m_hParent, playInfo.nId};
		//m_key.nId = playInfo.nId;
		hWnd = m_playWndMap[playInfo.nId]->m_hWnd;
	}

	if(!PlManager::Instance()->SetUserData(hWnd, m_pUser))
	{
		//printf("SetUserData\n");
		return FALSE;
	}

	::SendMessage(hWnd, WM_OWN_SETFOCUS, 0, 0);
	bRet = PlManager::Instance()->Play(hWnd, playInfo);

	return bRet;
}

HWND CPlCtrl::GetNextPlayWnd()
{
	PlayWndMap::iterator it = m_playWndMap.begin();
	for(; it!=m_playWndMap.end(); ++it)
	{
		if(!PlManager::Instance()->IsPlaying(it->second->m_hWnd))
			return it->second->m_hWnd;
	}
	return GetFocusWnd();
}

BOOL CPlCtrl::GetWndParm(char *pRet, int nType)
{
	//WindowKey key = {m_hParent, 0};
	BOOL bRet = FALSE;
	char wndinfo[2048] = {0};
	if(nType == FOCUS_WINDOW)
	{
		int nId = GetWindowLong(GetFocusWnd(), GWL_ID);
		bRet = PlManager::Instance()->GetWndPlayParm(m_playWndMap[nId]->m_hWnd, wndinfo);
	}
	else if(nType == ALL_WINDOW)
	{
		char ppWndInfo[64][64];
		int nWndNum = m_playWndMap.size();
		int nRealNum = 0;
		for (int i=0; i<nWndNum; ++i)
		{
			memset(ppWndInfo[i], 0, 64);
			//m_key.nId = i + (UINT)m_hParent;
			bRet = PlManager::Instance()->GetWndPlayParm(m_playWndMap[i]->m_hWnd, ppWndInfo[i]);
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

void CPlCtrl::SleepPlayer(bool bSleep)
{
	PlayWndMap::iterator it = m_playWndMap.begin();
	for(; it!=m_playWndMap.end(); ++it)
		PlManager::Instance()->SleepPlayer(it->second->m_hWnd, bSleep);
}

BOOL CPlCtrl::CreateWindows(const PL_LayoutInfo &layoutInfo)
{
	//WindowKey key = {m_hParent, 0};
	int nOldWnds = m_playWndMap.size();//CalcWndNum(m_layoutInfo);
	int nWindows = CalcWndNum(layoutInfo);
	if (nOldWnds < nWindows)
	{
		switch(m_layoutInfo.nMod)
		{
		case STREAME_REALTIME:		//real
			//TRACE("%d\n", GetTickCount());
			for(int i=nOldWnds; i<nWindows; ++i)
			{
				CPlWnd *r_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i));
				r_tmp->Init();
				::ShowWindow(((CWnd*)r_tmp)->m_hWnd, SW_SHOW);
				r_tmp->SetFullModel(m_layoutInfo.nMax);
				PlManager::Instance()->SetUserData(r_tmp->m_hWnd, m_pUser);
				//m_key.nId = i + (UINT)m_hParent;
				m_playWndMap[i] = r_tmp;
			}
			//TRACE("%d\n", GetTickCount());
			break;
		case STREAME_FILE:				//vod
			for(int i=nOldWnds; i<nWindows; ++i)
			{
				CPlWnd *v_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("v_play", m_hParent, i));
				v_tmp->Init();
				::ShowWindow(((CWnd*)v_tmp)->m_hWnd, SW_SHOW);
				v_tmp->SetFullModel(m_layoutInfo.nMax);
				PlManager::Instance()->SetUserData(v_tmp->m_hWnd, m_pUser);
				//m_key.nId = i + (UINT)m_hParent;
				m_playWndMap[i] = v_tmp;
			}
			break;
		default:
			return FALSE;
		}
	}
	else
	{
		//显示需要显示的窗口
		for (int i=0; i<nWindows; ++i)
		{
			CPlWnd *r_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i));
			r_tmp->Init();
			::ShowWindow(((CWnd*)r_tmp)->m_hWnd, SW_SHOW);
		}
		//隐藏不需要显示的窗口
		for (int i=nWindows; i<nOldWnds; ++i)
		{
			CPlWnd *r_tmp = dynamic_cast<CPlWnd *>(CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i));
			r_tmp->Init();
			::ShowWindow(((CWnd*)r_tmp)->m_hWnd, SW_HIDE);
		}
	}

	return TRUE;
}

void CPlCtrl::DestroyWindows()
{
	PlayWndMap::iterator it = m_playWndMap.begin();
	for(; it!=m_playWndMap.end(); ++it)
	{
		CPlFactoryWnd::Instance()->DelWindow(m_hParent, it->first);
	}
	m_playWndMap.clear();
}