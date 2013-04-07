#pragma once

#ifndef __NP_PLUGIN_H__
#define __NP_PLUGIN_H__

#include <windows.h>
#include <windowsx.h>
#include <map>
#include <string>
#include "npapi.h"
#include "npruntime.h"
#include "stdint.h"
#include "pl_ctrl.h"

#ifdef NP_PLUGIN_EXPORTS
#define NP_PLUGIN_API __declspec(dllexport)
#else
#define NP_PLUGIN_API __declspec(dllimport)
#endif


class /*NP_PLUGIN_API*/ CNPPlugin
{
private:
	NPWindow		*m_Window; 
	NPBool			m_bInitialized;
	NPObject		*m_pScriptableObject;
	HWND			m_hWnd;

public:
	NPP m_pNPInstance;
	NPObject *m_pWindowObj;

public:
	CNPPlugin(NPP pNPInstance);
	~CNPPlugin();

	NPBool init(NPWindow* pNPWindow);
	void shut();
	NPBool isInitialized(); 
	int16 handleEvent(void* event);
	void showVersion();
	void clear();
	void getVersion(char* *aVersion);
	NPObject *GetScriptableObject();
	
	/************************/

	void DefaultInvoke(UINT nType, int args[],UINT argCount);
	void RegisterCallBack(NPObject *CallBackFunc,UINT type);
	bool SetWorkModel(char *js_workmodel,NPVariant *result);
	bool Play(char *js_playInfo,NPVariant *result);
	bool SetLayout(char *js_layout,NPVariant *result);
	bool SetLayout();
	bool StopAllPlay(NPVariant *result);
	bool VodPlayJump(char *js_time,NPVariant *result);
	bool GetWndParm(int nType,NPVariant *result);
	bool SleepPlayer(bool bSleep,NPVariant *result);

	static void OnEvent(void *pUser,UINT nType, int args[],UINT argCount);

private:
	static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
	bool SetRetValue(char *psz_ret,NPVariant *result);

private:
	CPlCtrl *m_PlayCtrl;
	NPObject *m_CallBkPtz;
	NPObject *m_CallBkState;
	NPObject *m_CallBkVod;

	static WNDPROC CNPPlugin::lpOldProc;
};

#endif // __NP_PLUGIN_H__
