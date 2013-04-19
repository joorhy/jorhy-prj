#include "stdlib.h"
#include "np_plugin.h"
#include "np_script_plugin_object.h"
#include "pl_ctrl.h"
#include <map>

WNDPROC CNPPlugin::lpOldProc = NULL;

CNPPlugin::CNPPlugin(NPP pNPInstance) :
m_pNPInstance(pNPInstance),
m_pWindowObj(NULL),
m_bInitialized(FALSE),
m_pScriptableObject(NULL)
{
	m_hWnd = NULL;
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &m_pWindowObj);
}

CNPPlugin::~CNPPlugin()
{
	if(NULL != m_CallBkPtz)
	{
		NPN_ReleaseObject(m_CallBkPtz);
		m_CallBkPtz = NULL;
	}
	if(NULL != m_CallBkState)
	{
		NPN_ReleaseObject(m_CallBkState);
		m_CallBkState = NULL;
	}
	if(NULL != m_CallBkVod)
	{
		NPN_ReleaseObject(m_CallBkVod);
		m_CallBkVod = NULL;
	}
}

NPBool CNPPlugin::init(NPWindow* pNPWindow)
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

	LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
	style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	SetWindowLong(m_hWnd, GWL_STYLE, style);

	m_Window = pNPWindow;
	m_bInitialized = TRUE;

	m_CallBkPtz	= NULL;
	m_CallBkState = NULL;
	m_CallBkVod = NULL;
	CPlCtrl::CreateInstance(m_hWnd)->RegisterCallBack(OnEvent, this);

	return TRUE;
}

void CNPPlugin::shut()
{
	// subclass it back
	//SubclassWindow(m_hWnd, lpOldProc);
	(WNDPROC) SetWindowLongPtr( m_hWnd,
								GWLP_WNDPROC,
								(LONG_PTR)lpOldProc );
	CPlCtrl::ReleaseInstance(m_hWnd);
	m_hWnd = NULL;
	m_bInitialized = FALSE;
}

NPBool CNPPlugin::isInitialized()
{
	return m_bInitialized;
}

int16 CNPPlugin::handleEvent(void* event)
{
	return 0;
}

// this will force to draw a version string in the plugin window
void CNPPlugin::showVersion()
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
void CNPPlugin::clear()
{
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);
}

void CNPPlugin::getVersion(char* *aVersion)
{
	const char *ua = NPN_UserAgent(m_pNPInstance);
	char*& version = *aVersion;
	version = (char*)NPN_MemAlloc(1 + strlen(ua));
	if (version)
		strcpy(version, ua);
	strcpy(version, "");
}

NPObject * CNPPlugin::GetScriptableObject()
{
	if (!m_pScriptableObject)
		m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));

	if (m_pScriptableObject) 
		NPN_RetainObject(m_pScriptableObject);

	return m_pScriptableObject;
}

LRESULT CALLBACK CNPPlugin::PluginWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CNPPlugin *ud = (CNPPlugin*)GetWindowLong(hwnd,GWL_USERDATA);
	if(ud)
	{
		switch(message)
		{
		case WM_NULL:
			break;
		case WM_ERASEBKGND:
			RECT rect;
			GetClientRect(hwnd, &rect);
			FillRect((HDC)wParam, &rect, (HBRUSH) (COLOR_WINDOW+1));
			return 1;

		default:
			
			break;

		}
		if(ud->lpOldProc)
			return CallWindowProc(ud->lpOldProc,hwnd,message,wParam,lParam);
	}
		return DefWindowProc(hwnd, message, wParam, lParam);
}

void CNPPlugin::RegisterCallBack(NPObject *CallBackFunc,UINT type)
{
	switch(type)
	{
	case CALLBACK_PTZCTL:
		m_CallBkPtz	= CallBackFunc;
		NPN_RetainObject(m_CallBkPtz);
		break;

	case CALLBACK_ONSTATE:
		m_CallBkState = CallBackFunc;
		NPN_RetainObject(m_CallBkState);
		break;

	case CALLBACK_ONVOD:
		m_CallBkVod = CallBackFunc;
		NPN_RetainObject(m_CallBkVod);
		break;

	default:
		break;
	}
}

void CNPPlugin::OnEvent(void *pUser,UINT nType, int args[],UINT argCount)
{
	CNPPlugin *pThis = reinterpret_cast<CNPPlugin*>(pUser);
	if(pThis)
		pThis->DefaultInvoke(nType,args,argCount);
}

void CNPPlugin::DefaultInvoke(UINT nType, int args[],UINT argCount)
{
	NPVariant result;
	switch(nType)
	{
	case CALLBACK_PTZCTL:
		{
			if(NULL == m_CallBkPtz) return;
			if(args[1]  <= 0) return;

			NPVariant NPN_args[3];
			INT32_TO_NPVARIANT(		args[0],		NPN_args[0]);
			STRINGZ_TO_NPVARIANT(	(char*)args[1],	NPN_args[1]);
			INT32_TO_NPVARIANT(		args[2],		NPN_args[2]);

			NPN_InvokeDefault(m_pNPInstance,m_CallBkPtz,NPN_args,argCount,&result);
			break;
		}

	case CALLBACK_ONSTATE:
		{
			if(NULL == m_CallBkState) return;
			if(args[1] <= 0) return;

			NPVariant NPN_args[2];
			INT32_TO_NPVARIANT(		args[0],		NPN_args[0]);
			STRINGZ_TO_NPVARIANT(	(char*)args[1],	NPN_args[1]);
			NPN_InvokeDefault(m_pNPInstance,m_CallBkState,NPN_args,argCount,&result);
			break;
		}
	case CALLBACK_ONVOD:
		{
			if(NULL == m_CallBkVod) return;
			NPVariant NPN_args[1];
			INT32_TO_NPVARIANT(	*(int64_t*)args[0],NPN_args[0]);
			NPN_InvokeDefault(m_pNPInstance,m_CallBkVod,NPN_args,argCount,&result);
			break;
		}
	default:
		break;
	}
}

bool CNPPlugin::SetWorkModel(char *js_workmodel,NPVariant *result)
{

	if(CPlCtrl::CreateInstance(m_hWnd)->InitDisPlay(m_hWnd,js_workmodel))
		SetRetValue("{\"rst\":0}",result);
	else
		SetRetValue("{\"rst\":-1}",result);

	return true;
}

bool CNPPlugin::Play(char *js_playInfo,NPVariant *result)
{
	if(CPlCtrl::CreateInstance(m_hWnd)->Play(js_playInfo))
		SetRetValue("{\"rst\":0}",result);
	else	
		SetRetValue("{\"rst\":1}",result);
	return true;
}

bool CNPPlugin::ChangeLayout(char *js_layout,NPVariant *result)
{
	if(CPlCtrl::CreateInstance(m_hWnd)->SetLayout(js_layout))
		SetRetValue("{\"rst\":0}",result);

	return true;
}

bool CNPPlugin::SetLayout()
{
	CPlCtrl::CreateInstance(m_hWnd)->SetLayout();
	return true;
}

bool CNPPlugin::StopAllPlay(NPVariant *result)
{
	if(CPlCtrl::CreateInstance(m_hWnd)->StopAll())
		SetRetValue("{\"rst\":0}",result);
	else
		SetRetValue("{\"rst\":101}",result);

	return true;
}

bool CNPPlugin::VodPlayJump(char *js_time,NPVariant *result)
{
	if(CPlCtrl::CreateInstance(m_hWnd)->VodStreamJump(js_time))
		SetRetValue("{\"rst\":0}",result);
	else
		SetRetValue("{\"rst\":4}",result);

	return true;
}

bool CNPPlugin::GetWndParm(int nType,NPVariant *result)
{
	char info[1024] = {0};
	if(CPlCtrl::CreateInstance(m_hWnd)->GetWndParm(info,nType))
		SetRetValue(info,result);

	return true;
}

bool CNPPlugin::SleepPlayer(bool bSleep,NPVariant *result)
{
	CPlCtrl::CreateInstance(m_hWnd)->SleepPlayer(bSleep);
	SetRetValue("{\"rst\":0}",result);
	return true;
}

bool CNPPlugin::SetRetValue(char *psz_ret,NPVariant *result)
{
	int len = strlen(psz_ret);
	char *tmp = (char*)NPN_MemAlloc(len+1);
	strncpy(tmp,psz_ret,len);
	tmp[len] = '\0';
	STRINGZ_TO_NPVARIANT(tmp,*result);

	return true;
}