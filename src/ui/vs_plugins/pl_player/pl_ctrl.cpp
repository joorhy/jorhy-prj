#include "StdAfx.h"
#include "pl_ctrl.h"
#include "pl_type.h"
#include "pl_factory.h"
#include "pl_factory_wnd.h"
#include "pl_json_parser.h"
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
	for(int i=size-1; i>=0; --i)
	{
		CPlFactoryWnd::Instance()->DelWindow(i + 1);
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
			CPlWnd *r_tmp = (CPlWnd *)CPlFactoryWnd::Instance()->GetWindow("r_play", hParent, i+1);
			m_vecPlayWnd.push_back(r_tmp);
		}
		break;
	case STREAME_FILE:		//vod
		for(int i=0; i<nWindows; ++i)
		{
			CPlWnd *v_tmp = (CPlWnd *)CPlFactoryWnd::Instance()->GetWindow("v_play", hParent, i+1);
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
				CPlWnd *r_tmp = (CPlWnd *)CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i+1);
				m_vecPlayWnd.push_back(r_tmp);
			}
			break;
		case STREAME_FILE:		//vod
			for(int i=nOldNum; i<nNewNum; ++i)
			{
				CPlWnd *v_tmp = (CPlWnd *)CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i+1);
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
	((CPlWnd*)m_vecPlayWnd[0])->SetNowShowWindow(nNewNum);
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

BOOL CPlCtrl::Play(HWND hWnd,char *js_mrl)
{
	int size = m_vecPlayWnd.size();
	int i = 0;
	BOOL bRet = FALSE;
	for(i=0; i<size; ++i)
	{
		if(hWnd == ((CWnd*)m_vecPlayWnd[i])->m_hWnd)
		{
			bRet = PlManager::Instance()->Play(hWnd, js_mrl, STREAME_REALTIME, VLC_VIDEO);
			break;
		}
	}
	return bRet;	
}

void CPlCtrl::SetAllFullModel(UINT nType)
{
	int size = m_vecPlayWnd.size();
	for(int i=0; i<size; ++i)
	{
		((CPlWnd*)m_vecPlayWnd[i])->SetFullModel(nType);
	}
}

HWND CPlCtrl::GetFocusWnd()
{
	return ((CPlWnd*)m_vecPlayWnd[0])->GetFocusWnd(); 
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

BOOL CPlCtrl::RegisterCallBack(CALLBACK_onEvent funcAddr, void *pUser)
{
	m_pUser = pUser;
	return PlManager::RegisterCallBack(funcAddr);
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
	BOOL bRet = FALSE;
	HWND hWnd = GetFocusWnd();
	int nSize = m_vecPlayWnd.size();
	for(int i=0; i<nSize; ++i)
	{
		if(hWnd == ((CWnd*)m_vecPlayWnd[i])->m_hWnd)
		{
			bRet = PlManager::Instance()->VodStreamJump(hWnd, js_time);
			break;
		}
	}
	return bRet;
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
	json_object *playInfo = NULL;
	json_object *tmp = NULL;
	BOOL bRet = FALSE;

	playInfo = json_tokener_parse(js_mrl);
	if(is_error(playInfo))
	{
		return FALSE;
	}
	tmp = json_object_object_get(playInfo,"id");
	if(is_error(tmp))
	{
		return FALSE;
	}
	int wndId = json_object_get_int(tmp);
	if(0 == wndId)
	{
		bRet = Play(GetNextPlayWnd(),js_mrl);
	}
	else
	{
		int nSize = m_vecPlayWnd.size();
		if(wndId > nSize || wndId < 0) 
			return FALSE;
		HWND hWnd = ((CPlWnd*)m_vecPlayWnd[wndId])->m_hWnd;
		bRet = PlManager::Instance()->Play(hWnd, js_mrl, 0, 0);
	}
	json_object_put(playInfo);
	json_object_put(tmp);

	return bRet;
}

HWND CPlCtrl::GetNextPlayWnd()
{
	int nWndNum = FindShowWndNum();
	for(int i=0; i<nWndNum; ++i)
	{
		if(!PlManager::Instance()->IsPlaying(((CPlWnd*)m_vecPlayWnd[i])->m_hWnd))
		{
			return ((CPlWnd*)m_vecPlayWnd[i])->m_hWnd;
		}
	}
	//return ((CPlayWnd*)m_vctPlayWnd[0])->m_hWnd;
	return GetFocusWnd();
}

BOOL CPlCtrl::GetWndParm(char *pRet,int nType)
{
	BOOL bRet = FALSE;
	char wndinfo[64] = {0};
	if(nType == FOCUS_WINDOW)
	{
		int nId = GetWindowLong(GetFocusWnd(), GWL_ID);
		bRet = PlManager::Instance()->GetWndPlayParm(((CPlWnd*)m_vecPlayWnd[nId-1])->m_hWnd, wndinfo);
		if(bRet)
		{
			strcat(pRet,wndinfo);
		}
	}
	else if(nType == ALL_WINDOW)
	{
		json_object *allInfo = NULL;
		json_object *tmp	= NULL;

		int nSize = m_vecPlayWnd.size();
		allInfo = json_object_new_array();
		for(int i=0; i<nSize; ++i)
		{
			memset(wndinfo,0,sizeof(wndinfo));
			bRet = PlManager::Instance()->GetWndPlayParm(((CPlWnd*)m_vecPlayWnd[i])->m_hWnd, wndinfo);
			if(bRet)
			{
				tmp = json_tokener_parse(wndinfo);
				if(is_error(tmp))
				{
					continue;
				}
				json_object_array_add(allInfo,tmp);
			}
		}
		sprintf(pRet,"%s",json_object_to_json_string(allInfo));
		json_object_put(allInfo);
	}

	return bRet;
}

BOOL CPlCtrl::SetAllUserData()
{
	int nWndNum = FindShowWndNum();
	if(!m_pUser)
		return FALSE;
	for(int i=0; i<nWndNum; ++i)
	{
		if(!PlManager::Instance()->SetUserData(((CPlWnd*)m_vecPlayWnd[i])->m_hWnd, m_pUser))
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
		PlManager::Instance()->SleepPlayer(bSleep);
	}
}

void CPlCtrl::LoadPlLibrary()
{
	CString sPath;   
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer();   
	int nPos;   
	nPos = sPath.ReverseFind('\\');   
	sPath = sPath.Left(nPos);   
	sPath += "\\plugins";

	WIN32_FIND_DATAA ffd;
	LARGE_INTEGER filesize;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;
	CString szDir = sPath + "\\*.dll";
	hFind = FindFirstFileA(szDir.GetString(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind) 
		return;

	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			CString filename = ffd.cFileName;
			if (filename.Find("pl_hik") != -1 || filename.Find("pl_jo") != -1 || filename.Find("pl_vlc") != -1 /*|| filename.Find("pl_ui") != -1*/)
			{
				CString filedir = sPath+"\\"+filename;
				HMODULE hDllLib = LoadLibrary(filedir);
				dwError = GetLastError();
				m_vecModule.push_back(hDllLib);
			}	
		}
	}while (FindNextFileA(hFind, &ffd) != 0);

	//dwError = GetLastError();
	//if (dwError != ERROR_NO_MORE_FILES)
	//	return;

	FindClose(hFind);
}

void CPlCtrl::FreePlLibrary()
{
	std::vector<HMODULE>::iterator it = m_vecModule.begin();
	for (; it!=m_vecModule.end(); it++)
	{
		FreeLibrary(*it);
	}
	m_vecModule.clear();
}