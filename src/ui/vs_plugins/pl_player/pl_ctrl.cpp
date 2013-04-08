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
	int size = m_vctPlayWnd.size();
	for(int i=size-1;i>=0;i--)
	{
		if(m_nModel == REALMODEL)
		{
			delete m_vctPlayWnd[i];
		}
		else
		{
			delete m_vctPlayWnd[i];
		}
		m_vctPlayWnd.pop_back();
	}
}

BOOL CPlCtrl::InitDisPlay(HWND hParent,char* js_workMode)
{
	if(m_hParent != NULL)
	{
		return TRUE;
	}
	json_object *WorkMode = json_tokener_parse(js_workMode);
	if(is_error(WorkMode))
	{
		return FALSE;
	}
	m_nModel = json_object_get_int(json_object_object_get(WorkMode,"mod"));
	m_nLayout = json_object_get_int(json_object_object_get(WorkMode,"layout"));
	m_nWindows = json_object_get_int(json_object_object_get(WorkMode,"windows"));
	m_nMaxmodel = json_object_get_int(json_object_object_get(WorkMode,"max"));
	m_nUid = json_object_get_int(json_object_object_get(WorkMode,"uid"));

	char *tmpstr = json_object_get_string(json_object_object_get(WorkMode,"imgPath"));
	if(tmpstr)
		strcpy(m_szImagePath,tmpstr);
	tmpstr = json_object_get_string(json_object_object_get(WorkMode,"videoPath"));
	if(tmpstr)
		strcpy(m_szVideoPath,tmpstr);

	json_object_put(WorkMode);
	int numWindow = FindShowWndNum();
	
	switch(m_nModel)
	{
	case REALMODEL:		//real
		for(int i=0; i<numWindow;i++)
		{
			CWnd *r_tmp = CPlFactoryWnd::Instance()->GetWindow("r_play", hParent, i+1);
			m_vctPlayWnd.push_back(r_tmp);
		}
		break;

	case VODMODEL:		//vod
		for(int i=0; i<numWindow;i++)
		{
			CWnd *v_tmp = CPlFactoryWnd::Instance()->GetWindow("v_play", hParent, i+1);
			m_vctPlayWnd.push_back(v_tmp);
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
	if(3 == m_nLayout)
	{
		switch(m_nWindows)
		{
		case 0:	return 1;
		case 1:	return 4;
		case 2: return 9;
		case 3: return 16;
		}
	}
	return m_nWindows;
}

int CPlCtrl::FindShowWndNum(int layout,int windows)
{
	if(3 == layout)
	{
		switch(windows)
		{
		case 0:	return 1;
		case 1:	return 4;
		case 2: return 9;
		case 3: return 16;
		}
	}
	return windows;
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

BOOL CPlCtrl::SetLayout(int Layout,int Windows,int Maxmodel)
{
	int oldNum = m_vctPlayWnd.size();
	int displayNum = FindShowWndNum();
	int newNum = FindShowWndNum(Layout,Windows);
	if(oldNum < newNum)
	{
		switch(m_nModel)
		{
		case REALMODEL:		//real
			for(int i=0; i<newNum - oldNum;i++)
			{
				CWnd *r_tmp = CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i+1);
				m_vctPlayWnd.push_back(r_tmp);
			}
			break;

		case VODMODEL:		//vod
			for(int i=0; i<newNum - oldNum;i++)
			{
				CWnd *v_tmp = CPlFactoryWnd::Instance()->GetWindow("r_play", m_hParent, i+1);
				m_vctPlayWnd.push_back(v_tmp);
			}
			break;
		}
	}
	CRect rect;
	GetClientRect(m_hParent,&rect);
	ShowAllowWindow(newNum,displayNum);
	switch(Layout)
	{
	case 1:
		for(int i=0;i<newNum;i++)
		{
			((CWnd*)m_vctPlayWnd[i])->MoveWindow(rect.left+i*rect.Width() / newNum,
										rect.top,
										rect.Width() / newNum,					
										rect.Height());
		}
		break;

	case 2:
		for(int i=0;i<newNum;i++)
		{
			((CWnd*)m_vctPlayWnd[i])->MoveWindow(rect.left,		
										rect.top+i*rect.Height() / newNum,
										rect.Width(),	
										rect.Height() / newNum);
		}
		break;

	case 3:
		switch(Windows)
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
	SetAllFullModel(Maxmodel);
	((CPlWnd*)m_vctPlayWnd[0])->SetNowShowWindow(newNum);
	::SendMessage(GetFocusWnd(),WM_OWN_SETFOCUS,0,0);
	return TRUE;
}

void CPlCtrl::GridWindow(int windowNum)
{
	CRect rect;
	GetClientRect(m_hParent,&rect);
	int num = sqrt((double)windowNum);
	for(int i=0;i<num;i++)
		{
			for(int j=0;j<num;j++)
			{
				((CWnd*)m_vctPlayWnd[i*num+j])->MoveWindow(rect.left + j*rect.Width() / num,
												rect.top + i*rect.Height() / num,
												rect.Width() / num,
												rect.Height() / num);
			}
		}
}


BOOL CPlCtrl::Play(HWND hWnd,char *js_mrl)
{
	int size = m_vctPlayWnd.size();
	int i = 0;
	BOOL bRet = FALSE;
	for(i=0;i<size;i++)
	{
		if(hWnd == ((CWnd*)m_vctPlayWnd[i])->m_hWnd)
		{
			bRet = ((CPlWnd*)m_vctPlayWnd[i])->GetPlayer()->Play(hWnd,js_mrl);
			break;
		}
	}
	return bRet;
	
}

void CPlCtrl::SetAllFullModel(UINT nType)
{
	int size = m_vctPlayWnd.size();
	for(int i=0;i<size;i++)
	{
		((CPlWnd*)m_vctPlayWnd[i])->SetFullModel(nType);
	}
}

HWND CPlCtrl::GetFocusWnd()
{
	return ((CPlWnd*)m_vctPlayWnd[0])->GetFocusWnd(); 
}

void CPlCtrl::ShowAllowWindow(int nNewNum,int nOldNum)
{
	if(nNewNum < nOldNum)
	{
		for(int i=nNewNum;i<nOldNum;i++)
		{
			::ShowWindow(((CWnd*)m_vctPlayWnd[i])->m_hWnd,SW_HIDE);
		}
	}
	else if(nOldNum < nNewNum)
	{
		for(int i=nOldNum;i<nNewNum;i++)
		{
			::ShowWindow(((CWnd*)m_vctPlayWnd[i])->m_hWnd,SW_SHOW);
		}
	}
}

BOOL CPlCtrl::RegisterCallBack(CALLBACK_onEvent funcAddr,void *pUser)
{
	m_pUser = pUser;
	return PlManager::RegisterCallBack(funcAddr);
}

BOOL CPlCtrl::StopAll()
{
	int size = m_vctPlayWnd.size();
	for(int i=0;i<size;i++)
	{
		((CPlWnd*)m_vctPlayWnd[i])->GetPlayer()->Stop();
	}
	return TRUE;
}

BOOL CPlCtrl::VodStreamJump(char *js_time)
{
	if(m_nModel == REALMODEL) return FALSE;
	BOOL bRet = FALSE;
	HWND wnd = GetFocusWnd();
	int size = m_vctPlayWnd.size();
	for(int i=0;i<size;i++)
	{
		if(wnd == ((CWnd*)m_vctPlayWnd[i])->m_hWnd)
		{
			bRet = ((CPlWnd*)m_vctPlayWnd[i])->GetPlayer()->VodStreamJump(js_time);
			break;
		}
	}
	return bRet;
}

BOOL CPlCtrl::GetPath(char *psz_dest,UINT nType)
{
	if(nType == IMAGEPATH)
	{
		strncpy(psz_dest,m_szImagePath,PATH_LENGTH);
	}
	else if(nType == VIDEOPATH)
	{
		strncpy(psz_dest,m_szVideoPath,PATH_LENGTH);
	}

	return TRUE;
}

BOOL CPlCtrl::SetLayout()
{
	if(m_nLayout == -1) return FALSE;
	return SetLayout(m_nLayout,m_nWindows,m_nMaxmodel);
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
		int size = m_vctPlayWnd.size();
		if(wndId > size || wndId < 0) return FALSE;
		HWND hWnd = ((CPlWnd*)m_vctPlayWnd[wndId])->m_hWnd;
		bRet = ((CPlWnd*)m_vctPlayWnd[wndId])->GetPlayer()->Play(hWnd,js_mrl);
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
	int WndNum = FindShowWndNum();
	for(int i=0;i<WndNum;i++)
	{
		if(!((CPlWnd*)m_vctPlayWnd[i])->GetPlayer()->IsPlaying())
		{
			return ((CPlWnd*)m_vctPlayWnd[i])->m_hWnd;
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
		int id = GetWindowLong(GetFocusWnd(),GWL_ID);
		bRet = ((CPlWnd*)m_vctPlayWnd[id-1])->GetPlayer()->GetWndPlayParm(wndinfo);
		if(bRet)
		{
			strcat(pRet,wndinfo);
		}
	}
	else if(nType == ALL_WINDOW)
	{
		json_object *allInfo = NULL;
		json_object *tmp	= NULL;

		int size = m_vctPlayWnd.size();
		allInfo = json_object_new_array();
		for(int i=0;i<size;i++)
		{
			memset(wndinfo,0,sizeof(wndinfo));
			bRet = ((CPlWnd*)m_vctPlayWnd[i])->GetPlayer()->GetWndPlayParm(wndinfo);
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
	int WndNum = FindShowWndNum();
	if(!m_pUser)
		return FALSE;
	for(int i=0;i<WndNum;i++)
	{
		if(!((CPlWnd*)m_vctPlayWnd[i])->GetPlayer()->SetUserData(m_pUser))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CPlCtrl::SleepPlayer(bool bSleep)
{
	int WndNum = FindShowWndNum();
	for(int i=0;i<WndNum;i++)
	{
		((CPlWnd*)m_vctPlayWnd[i])->GetPlayer()->SleepPlayer(bSleep);
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