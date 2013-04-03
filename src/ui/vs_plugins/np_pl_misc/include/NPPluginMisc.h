#pragma once

#include <windows.h>
#include <windowsx.h>
#include "npapi.h"
#include "npruntime.h"

#ifdef NP_PLUGIN_MISC_EXPORTS
#define NP_PLUGIN_API __declspec(dllexport)
#else
#define NP_PLUGIN_API __declspec(dllimport)
#endif

class CNPPluginMisc
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
	CNPPluginMisc(NPP pNPInstance);
	~CNPPluginMisc();

	NPBool init(NPWindow* pNPWindow);
	void shut();
	NPBool isInitialized(); 
	int16 handleEvent(void* event);
	void showVersion();
	void clear();
	void getVersion(char* *aVersion);
	NPObject *GetScriptableObject();

	/************************/
	bool SelectFolder(NPVariant *result);

private:
	static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
	bool SetRetValue(char *psz_ret,NPVariant *result);
	bool SelectFolder(char *szDir,HWND m_hWnd);
	static int CALLBACK BrowseFolderCBK(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData);
	static bool IsDirectoryWrite(char* filePath);

private:
	static WNDPROC lpOldProc;
};
