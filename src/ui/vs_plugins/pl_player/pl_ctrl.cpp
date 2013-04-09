#include "StdAfx.h"
#include "pl_ctrl.h"
#include "pl_type.h"
#include "pl_factory.h"
#include "pl_factory_wnd.h"
#include "pl_wnd.h"
#include <cmath>
using namespace std;

char CPlCtrl::m_szImagePath[512] = {0};
char CPlCtrl::m_szVideoPath[512] = {0};

CPlCtrl::CPlCtrl(void)
{
	m_hParent	= NULL;
	m_nModel	= -1;
	m_nLayout	= -1;
	m_nWindows	= -1;
	m_nMaxmodel = -1;
	m_nUid		= -1;
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

BOOL CPlCtrl::InitDisPlay(HWND hParent,char* js_workMode)
{
	if(m_hParent != NULL)
		return TRUE;
	
	json_object *workMode = json_tokener_parse(js_workMode);
	if(is_error(workMode))
		return FALSE;
	
	m_nModel = json_object_get_int(json_object_object_get(workMode, "mod"));
	m_nLayout = json_object_get_int(json_object_object_get(workMode, "layout"));
	m_nWindows = json_object_get_int(json_object_object_get(workMode, "windows"));
	m_nMaxmodel = json_object_get_int(json_object_object_get(workMode, "max"));
	m_nUid = json_object_get_int(json_object_object_get(workMode, "uid"));

	char *tmpstr = json_object_get_string(json_object_object_get(workMode, "imgPath"));
	if(tmpstr)
		strcpy(m_szImagePath,tmpstr);
	tmpstr = json_object_get_string(json_object_object_get(workMode, "videoPath"));
	if(tmpstr)
		strcpy(m_szVideoPath,tmpstr);

	json_object_put(workMode);
	int nWindows = FindShowWndNum();
	
	switch(m_nModel)
	{
	case REALMODEL:		//real
		for(int i=0; i<nWindows; ++i)
		{
			CWnd *r_tmp = CPlFactoryWnd::Instance()->GetWindow("r_play", hParent, i+1);
			m_vecPlayWnd.push_back(r_tmp);
		}
		break;
	case VODMODEL:		//vod
		for(int i=0; i<nWindows; ++i)
		{
			CWnd *v_tmp = CPlFactoryWnd::Instance()->GetWindow("v_play", hParent, i+1);
			m_vecPlayWnd.push_back(v_tmp);
		}
		break;
	default:
		return FALSE;
	}
	m_hParent = hParent;
	SetLayout(m_nLayout,m_nWindows,m_nMaxmodel);
	SetAllUserData();
	return TRUE;
}


int CPlCtrl::FindShowWndNum()
{
	return FindShowWndNum(m_nLayout, m_nWindows);
}

int CPlCtrl::FindShowWndNum(int nLayout,int nWindows)
{
	int nWndNum = 1;
	if(3 == nLayout)
	{
		switch(nWindows)
		{
		case 0:	
			nWndNum = 1;
			break;
		case 1:	
			nWndNum = 4;
			break;
		case 2: 
			nWndNum = 9;
			break;
		case 3: 
			nWndNum = 16;
			break;
		}
	}
	return nWndNum;
}

BOOL CPlCtrl::SetLayout(char *js_Layout)
{
	json_object *layout = json_tokener_parse(js_Layout);
	if(is_error(layout))
	{
		return FALSE;
	}
	int Layout = json_object_get_int(json_object_object_get(layout,"layout"));
	int Windows = json_object_get_int(json_object_object_get(layout,"windows"));
	int Maxmodel = json_object_get_int(json_object_object_get(layout,"max"));
	if(SetLayout(Layout,Windows,Maxmodel))
	{
		m_nLayout = Layout;
		m_nWindows = Windows;
		m_nMaxmodel = Maxmodel;
		return TRUE;
	}
	return FALSE;
}

BOOL CPlCtrl::SetLayout(int nLayout, int nWndNum, int nMaxModel)
{
	int nOldNum = m_vecPlayWnd.size();
	int nDisplayNum = FindShowWndNum();
	int nNewNum = FindShowWndNum(nLayout, nWndNum);
	if(nOldNum < nNewNum)
	{
		switch(m_nModel)
		{
		case REALMODEL:		//real
			for(int i=nOldNum; i<nNewNum; ++i)
			{
				CWnd *r_tmp = CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i+1);
				m_vecPlayWnd.push_back(r_tmp);
			}
			break;
		case VODMODEL:		//vod
			for(int i=nOldNum; i<nNewNum; ++i)
			{
				CWnd *v_tmp = CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i+1);
				m_vecPlayWnd.push_back(v_tmp);
			}
			break;
		}
	}
	CRect rect;
	GetClientRect(m_hParent,&rect);
	ShowAllowWindow(nNewNum, nDisplayNum);
	switch(nLayout)
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
		switch(nWndNum)
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
	SetAllFullModel(nMaxModel);
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
			bRet = ((CPlWnd*)m_vecPlayWnd[i])->GetPlayer()->Play(hWnd, js_mrl);
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
			::ShowWindow(((CWnd*)m_vecPlayWnd[i])->m_hWnd,SW_SHOW);
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
		((CPlWnd*)m_vecPlayWnd[i])->GetPlayer()->Stop();
	}
	return TRUE;
}

BOOL CPlCtrl::VodStreamJump(char *js_time)
{
	if(m_nModel == REALMODEL) 
		return FALSE;
	BOOL bRet = FALSE;
	HWND hWnd = GetFocusWnd();
	int nSize = m_vecPlayWnd.size();
	for(int i=0; i<nSize; ++i)
	{
		if(hWnd == ((CWnd*)m_vecPlayWnd[i])->m_hWnd)
		{
			bRet = ((CPlWnd*)m_vecPlayWnd[i])->GetPlayer()->VodStreamJump(js_time);
			break;
		}
	}
	return bRet;
}

BOOL CPlCtrl::GetPath(char *psz_dest,UINT nType)
{
	if(nType == IMAGEPATH)
	{
		strncpy(psz_dest, m_szImagePath, PATH_LENGTH);
	}
	else if(nType == VIDEOPATH)
	{
		strncpy(psz_dest, m_szVideoPath, PATH_LENGTH);
	}

	return TRUE;
}

BOOL CPlCtrl::SetLayout()
{
	if(m_nLayout == -1) 
		return FALSE;
	return SetLayout(m_nLayout, m_nWindows, m_nMaxmodel);
}

BOOL CPlCtrl::Play(char *js_mrl)
{
	json_object *playInfo = NULL;
	json_object *tmp = NULL;
	BOOL bRet = FALSE;

#ifndef APACHE_TEST
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
		bRet = ((CPlWnd*)m_vecPlayWnd[wndId])->GetPlayer()->Play(hWnd,js_mrl);
	}
	json_object_put(playInfo);
	json_object_put(tmp);
#else
	bRet = Play(GetNextPlayWnd(),js_mrl);
#endif
	return bRet;
}

HWND CPlCtrl::GetNextPlayWnd()
{
	int nWndNum = FindShowWndNum();
	for(int i=0; i<nWndNum; ++i)
	{
		if(!((CPlWnd*)m_vecPlayWnd[i])->GetPlayer()->IsPlaying())
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
		bRet = ((CPlWnd*)m_vecPlayWnd[nId-1])->GetPlayer()->GetWndPlayParm(wndinfo);
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
			bRet = ((CPlWnd*)m_vecPlayWnd[i])->GetPlayer()->GetWndPlayParm(wndinfo);
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
		if(!((CPlWnd*)m_vecPlayWnd[i])->GetPlayer()->SetUserData(m_pUser))
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
		((CPlWnd*)m_vecPlayWnd[i])->GetPlayer()->SleepPlayer(bSleep);
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