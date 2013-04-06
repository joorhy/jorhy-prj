#pragma once

//#include "PlayerFactor.h"
#include "pl_type.h"
#include <vector>
#include "json.h"

class __declspec(dllexport) CPlayerCtrl
{
public:
	static CPlayerCtrl *CreateInstance();
	static int ReleaseInstance();

	CPlayerCtrl(void);
	~CPlayerCtrl(void);

public:
	BOOL InitDisPlay(HWND hParent,char* js_workMode);
	BOOL SetLayout(char *js_Layout);
	BOOL SetLayout();
	BOOL Play(char *js_mrl);
	BOOL Play(HWND hWnd,char *js_mrl);
	BOOL StopAll();
	BOOL VodStreamJump(char *js_time);
	BOOL GetWndParm(char *pRet,int nType);
	void SleepPlayer(bool bSleep);

	/**********************************************/
	char *GetLayout() const;
	void FullScreen();
	HWND GetFocusWnd();
	BOOL RegisterCallBack(CALLBACK_onEvent funcAddr,void *pUser);
	static BOOL GetPath(char *psz_dest,UINT nType);

private:
	HWND m_hParent;

	//work model
	int m_nModel;
	int m_nLayout;
	int m_nWindows;
	int m_nMaxmodel;
	int m_nUid;
	static char m_szImagePath[PATH_LENGTH];
	static char m_szVideoPath[PATH_LENGTH];
	std::vector<char *> m_vctPlayWnd; 
	void *m_pUser;

	static CPlayerCtrl *m_pInstance;
	static int m_nInstanceRef;

private:
	int FindShowWndNum();
	int FindShowWndNum(int layout,int windows);
	HWND GetNextPlayWnd();
	BOOL SetLayout(int Layout,int Windows,int Maxmodel);
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