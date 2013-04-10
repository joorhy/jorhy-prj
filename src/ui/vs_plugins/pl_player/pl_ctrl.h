#pragma once

#include "pl_core.h"
#include "pl_type.h"
#include "pl_player.h"
#include "pl_singleton.h"
#include "json.h"
#include <vector>

class CPlWnd;
class PL_API CPlCtrl : public SingletonTmpl<CPlCtrl>
{
public:
	CPlCtrl(void);
	~CPlCtrl(void);

public:
	BOOL	InitDisPlay(HWND hParent,char* js_workMode);
	BOOL	SetLayout(char *js_Layout);
	BOOL	SetLayout();
	BOOL	Play(char *js_mrl);
	BOOL	StopAll();
	BOOL	VodStreamJump(char *js_time);
	BOOL	GetWndParm(char *pRet,int nType);
	void		SleepPlayer(bool bSleep);

	/**********************************************/
	void FullScreen();
	HWND GetFocusWnd();
	BOOL RegisterCallBack(NpnNotifyFunc funcAddr, void *pUser);
	BOOL GetPath(char *psz_dest, UINT nType);

private:
	HWND m_hParent;
	//work model
	PL_LayoutInfo m_layoutInfo;
	std::vector<CPlWnd *> m_vecPlayWnd; 
	void *m_pUser;

private:
	int FindShowWndNum();
	int FindShowWndNum(const PL_LayoutInfo &layoutInfo);
	HWND GetNextPlayWnd();
	BOOL SetLayout(const PL_LayoutInfo &layoutInfo);
	void GridWindow(int windowNum);
	void SetAllFullModel(UINT nType);
	void ShowAllowWindow(int nNewNum,int nOldNum);
	BOOL SetAllUserData();
};

static void Convert(const char* strIn,char* strOut,int sourceCodepage,int targetCodepage)
{
	int len=lstrlen(strIn);
	int unicodeLen=MultiByteToWideChar(sourceCodepage,0,strIn,-1,NULL,0);
	wchar_t* pUnicode;
	pUnicode=new wchar_t[unicodeLen+1];
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage,0,strIn,-1,(LPWSTR)pUnicode,unicodeLen);
	BYTE * pTargetData = NULL;
	int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL);
	pTargetData=new BYTE[targetLen+1];
	memset(pTargetData,0,targetLen+1);
	WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL);
	lstrcpy(strOut,(char*)pTargetData);
	delete pUnicode;
	delete pTargetData;
}