#include "StdAfx.h"
#include "PlayerCtrl.h"
#include "DataCenter.h"
#include "RPlayWnd.h"
#include "VPlayWnd.h"
#include "PlayWnd.h"
#include <cmath>
using namespace std;

char CPlayerCtrl::m_szImagePath[512] = {0};
char CPlayerCtrl::m_szVideoPath[512] = {0};
CPlayerCtrl *CPlayerCtrl::m_pInstance= NULL;
int CPlayerCtrl::m_nInstanceRef	= NULL;

CPlayerCtrl *CPlayerCtrl::CreateInstance()
{
	if(NULL == m_pInstance)
		m_pInstance = new CPlayerCtrl();
	m_nInstanceRef++;
	return m_pInstance;
}

int CPlayerCtrl::ReleaseInstance()
{
	if(m_pInstance != NULL)
	{
		m_nInstanceRef--;
		if(m_nInstanceRef == 0)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
	return m_nInstanceRef;
}

CPlayerCtrl::CPlayerCtrl(void)
{
	m_hParent	= NULL;
	m_nModel	= -1;
	m_nLayout	= -1;
	m_nWindows	= -1;
	m_nMaxmodel = -1;
	m_nUid		= -1;
	m_pUser		= NULL;
}

CPlayerCtrl::~CPlayerCtrl(void)
{
	int size = m_vctPlayWnd.size();
	for(int i=size-1;i>=0;i--)
	{
		if(m_nModel == REALMODEL)
		{
			//delete (CRPlayWnd*)m_vctPlayWnd[i];
		}
		else
		{
			//delete (CVPlayWnd*)m_vctPlayWnd[i];
		}
		m_vctPlayWnd.pop_back();
	}
}

BOOL CPlayerCtrl::InitDisPlay(HWND hParent,char* js_workMode)
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
			//CRPlayWnd *tmp = new CRPlayWnd(hParent,i+1);
			//m_vctPlayWnd.push_back((char*)tmp);
		}
		break;

	case VODMODEL:		//vod
		for(int i=0; i<numWindow;i++)
		{
			//CVPlayWnd *tmp = new CVPlayWnd(hParent,i+1);
			//m_vctPlayWnd.push_back((char*)tmp);
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


int CPlayerCtrl::FindShowWndNum()
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

int CPlayerCtrl::FindShowWndNum(int layout,int windows)
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


BOOL CPlayerCtrl::SetLayout(char *js_Layout)
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

BOOL CPlayerCtrl::SetLayout(int Layout,int Windows,int Maxmodel)
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
				//CRPlayWnd *tmp = new CRPlayWnd(m_hParent,oldNum + i+1);
				//m_vctPlayWnd.push_back((char*)tmp);
			}
			break;

		case VODMODEL:		//vod
			for(int i=0; i<newNum - oldNum;i++)
			{
				//CVPlayWnd *tmp = new CVPlayWnd(m_hParent,oldNum + i+1);
				//m_vctPlayWnd.push_back((char*)tmp);
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
	((CPlayWnd*)m_vctPlayWnd[0])->SetNowShowWindow(newNum);
	::SendMessage(GetFocusWnd(),WM_OWN_SETFOCUS,0,0);
	return TRUE;
}

void CPlayerCtrl::GridWindow(int windowNum)
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


BOOL CPlayerCtrl::Play(HWND hWnd,char *js_mrl)
{
	int size = m_vctPlayWnd.size();
	int i = 0;
	BOOL bRet = FALSE;
	for(i=0;i<size;i++)
	{
		if(hWnd == ((CWnd*)m_vctPlayWnd[i])->m_hWnd)
		{
			bRet = ((CPlayWnd*)m_vctPlayWnd[i])->GetPlayer()->Play(hWnd,js_mrl);
			break;
		}
	}
	return bRet;
	
}

void CPlayerCtrl::SetAllFullModel(UINT nType)
{
	int size = m_vctPlayWnd.size();
	for(int i=0;i<size;i++)
	{
		((CPlayWnd*)m_vctPlayWnd[i])->SetFullModel(nType);
	}
}

HWND CPlayerCtrl::GetFocusWnd()
{
	return ((CPlayWnd*)m_vctPlayWnd[0])->GetFocusWnd(); 
}

void CPlayerCtrl::ShowAllowWindow(int nNewNum,int nOldNum)
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

BOOL CPlayerCtrl::RegisterCallBack(CALLBACK_onEvent funcAddr,void *pUser)
{
	m_pUser = pUser;
	return PlayerFactor::RegisterCallBack(funcAddr);
}

BOOL CPlayerCtrl::StopAll()
{
	int size = m_vctPlayWnd.size();
	for(int i=0;i<size;i++)
	{
		((CPlayWnd*)m_vctPlayWnd[i])->GetPlayer()->Stop();
	}
	return TRUE;
}

BOOL CPlayerCtrl::VodStreamJump(char *js_time)
{
	if(m_nModel == REALMODEL) return FALSE;
	BOOL bRet = FALSE;
	HWND wnd = GetFocusWnd();
	int size = m_vctPlayWnd.size();
	for(int i=0;i<size;i++)
	{
		if(wnd == ((CWnd*)m_vctPlayWnd[i])->m_hWnd)
		{
			bRet = ((CPlayWnd*)m_vctPlayWnd[i])->GetPlayer()->VodStreamJump(js_time);
			break;
		}
	}
	return bRet;
}

BOOL CPlayerCtrl::GetPath(char *psz_dest,UINT nType)
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

BOOL CPlayerCtrl::SetLayout()
{
	if(m_nLayout == -1) return FALSE;
	return SetLayout(m_nLayout,m_nWindows,m_nMaxmodel);
}

BOOL CPlayerCtrl::Play(char *js_mrl)
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
		HWND hWnd = ((CPlayWnd*)m_vctPlayWnd[wndId])->m_hWnd;
		bRet = ((CPlayWnd*)m_vctPlayWnd[wndId])->GetPlayer()->Play(hWnd,js_mrl);
	}
	
	json_object_put(playInfo);
	json_object_put(tmp);
#else
	bRet = Play(GetNextPlayWnd(),js_mrl);
#endif
	return bRet;
}

HWND CPlayerCtrl::GetNextPlayWnd()
{
	int WndNum = FindShowWndNum();
	for(int i=0;i<WndNum;i++)
	{
		if(!((CPlayWnd*)m_vctPlayWnd[i])->GetPlayer()->IsPlaying())
		{
			return ((CPlayWnd*)m_vctPlayWnd[i])->m_hWnd;
		}
	}
	//return ((CPlayWnd*)m_vctPlayWnd[0])->m_hWnd;
	return GetFocusWnd();
}

BOOL CPlayerCtrl::GetWndParm(char *pRet,int nType)
{
	BOOL bRet = FALSE;
	char wndinfo[64] = {0};
	if(nType == FOCUS_WINDOW)
	{
		int id = GetWindowLong(GetFocusWnd(),GWL_ID);
		bRet = ((CPlayWnd*)m_vctPlayWnd[id-1])->GetPlayer()->GetWndPlayParm(wndinfo);
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
			bRet = ((CPlayWnd*)m_vctPlayWnd[i])->GetPlayer()->GetWndPlayParm(wndinfo);
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


BOOL CPlayerCtrl::SetAllUserData()
{
	int WndNum = FindShowWndNum();
	if(!m_pUser)
		return FALSE;
	for(int i=0;i<WndNum;i++)
	{
		if(!((CPlayWnd*)m_vctPlayWnd[i])->GetPlayer()->SetUserData(m_pUser))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CPlayerCtrl::SleepPlayer(bool bSleep)
{
	int WndNum = FindShowWndNum();
	for(int i=0;i<WndNum;i++)
	{
		((CPlayWnd*)m_vctPlayWnd[i])->GetPlayer()->SleepPlayer(bSleep);
	}
}