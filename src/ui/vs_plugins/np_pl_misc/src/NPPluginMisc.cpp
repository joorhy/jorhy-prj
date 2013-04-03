#include "NPPluginMisc.h"
#include "plugin_object.h"
#include <shlobj.h>

WNDPROC CNPPluginMisc::lpOldProc = NULL;

CNPPluginMisc::CNPPluginMisc(NPP pNPInstance) :
m_pNPInstance(pNPInstance),
m_pWindowObj(NULL),
m_bInitialized(FALSE),
m_pScriptableObject(NULL)
{
	m_hWnd = NULL;
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &m_pWindowObj);
}

CNPPluginMisc::~CNPPluginMisc()
{

}

NPBool CNPPluginMisc::init(NPWindow* pNPWindow)
{
	if(pNPWindow == NULL)
		return FALSE;

	m_hWnd = (HWND)pNPWindow->window;
	if(m_hWnd == NULL)
		return FALSE;

	// subclass window so we can intercept window messages and
	// do our drawing to it
	//lpOldProc = SubclassWindow(m_hWnd, (WNDPROC)PluginWinProc);
	lpOldProc = (WNDPROC) SetWindowLongPtr( m_hWnd,
											GWLP_WNDPROC,
											(LONG_PTR)PluginWinProc );

	// associate window with our CPlugin object so we can access 
	// it in the window procedure
	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);

	m_Window = pNPWindow;
	m_bInitialized = TRUE;

	return TRUE;
}

void CNPPluginMisc::shut()
{
	(WNDPROC) SetWindowLongPtr( m_hWnd,
								GWLP_WNDPROC,
								(LONG_PTR)lpOldProc );
	m_hWnd = NULL;
	m_bInitialized = FALSE;
}

NPBool CNPPluginMisc::isInitialized()
{
	return m_bInitialized;
}

int16 CNPPluginMisc::handleEvent(void* event)
{
	return 0;
}

// this will force to draw a version string in the plugin window
void CNPPluginMisc::showVersion()
{
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);

	if (m_Window) 
	{
		NPRect r =
		{
			(uint16)m_Window->y, (uint16)m_Window->x,
			(uint16)(m_Window->y + m_Window->height),
			(uint16)(m_Window->x + m_Window->width)
		};
		NPN_InvalidateRect(m_pNPInstance, &r);
	}
}

// this will clean the plugin window
void CNPPluginMisc::clear()
{
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);
}

void CNPPluginMisc::getVersion(char* *aVersion)
{
	const char *ua = NPN_UserAgent(m_pNPInstance);
	char*& version = *aVersion;
	version = (char*)NPN_MemAlloc(1 + strlen(ua));
	if (version)
		strcpy(version, ua);
	strcpy(version, "");
}

NPObject * CNPPluginMisc::GetScriptableObject()
{
	if (!m_pScriptableObject)
		m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));

	if (m_pScriptableObject) 
		NPN_RetainObject(m_pScriptableObject);

	return m_pScriptableObject;
}

LRESULT CALLBACK CNPPluginMisc::PluginWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, message, wParam, lParam);
}

bool CNPPluginMisc::SelectFolder(NPVariant *result)
{
	char szDir[MAX_PATH] = {0};
	if(SelectFolder(szDir,m_hWnd))
		SetRetValue(szDir,result);
	return true;
}

bool CNPPluginMisc::SetRetValue(char *psz_ret,NPVariant *result)
{
	int len = strlen(psz_ret);
	char *tmp = (char*)NPN_MemAlloc(len+1);
	strncpy(tmp,psz_ret,len);
	tmp[len] = '\0';
	STRINGZ_TO_NPVARIANT(tmp,*result);

	return true;
}


bool CNPPluginMisc::SelectFolder(char *szDir,HWND m_hWnd)
{ 
	BROWSEINFO   bi; 
	ITEMIDLIST   *pidl; 
	BOOL bRet;

	bi.hwndOwner	= m_hWnd; 
	bi.pidlRoot		= NULL; 
	bi.pszDisplayName	=   szDir; 
	bi.lpszTitle	= "请选择目录 "; 
	bi.ulFlags		= BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT; 
	bi.lpfn			= BrowseFolderCBK; 
	bi.lParam		=   0; 
	bi.iImage		=   0; 

	pidl = SHBrowseForFolder(&bi); 
	if(pidl == NULL) 
		return FALSE; 
	bRet = SHGetPathFromIDList(pidl,szDir);
	return bRet;	
}

int CALLBACK CNPPluginMisc::BrowseFolderCBK(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	char dir[MAX_PATH] = {0};
	DWORD outlen = 0;
	SECURITY_DESCRIPTOR Outinfo;
	switch(uMsg)
	{
	case BFFM_SELCHANGED:
		if(SHGetPathFromIDList((LPITEMIDLIST)lParam ,dir))
		{
			if(IsDirectoryWrite(dir))
			{
				SendMessage(hwnd, BFFM_SETSTATUSTEXT,0,(LPARAM)"可用目录");
				SendMessage(hwnd, BFFM_ENABLEOK,0,(LPARAM)1);
			}
			else
			{
				SendMessage(hwnd, BFFM_SETSTATUSTEXT,0,(LPARAM)"无效目录,没有权限！");
				SendMessage(hwnd, BFFM_ENABLEOK,0,(LPARAM)0);
			}
		}  

		break;

	}
	return TRUE;
}

bool CNPPluginMisc::IsDirectoryWrite(char* filePath)
{
	BOOL bRet = FALSE;

	char tmpname[] = "ronyao123456897yuan.aa";
	char file[MAX_PATH + sizeof(tmpname)] = {0};
	sprintf(file,"%s%s",filePath,tmpname);
	FILE *hFile = fopen(file,"wb");
	if(hFile)
	{
		fclose(hFile);
		remove(file);
		bRet = TRUE;
	}
	else
		bRet = FALSE;

	return bRet;
}
