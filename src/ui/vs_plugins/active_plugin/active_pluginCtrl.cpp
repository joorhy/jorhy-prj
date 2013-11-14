// active_pluginCtrl.cpp : Implementation of the Cactive_pluginCtrl ActiveX Control class.

#include "stdafx.h"
#include "active_plugin.h"
#include "active_pluginCtrl.h"
#include "active_pluginPropPage.h"
#include "pl_ctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(Cactive_pluginCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(Cactive_pluginCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(Cactive_pluginCtrl, COleControl)
	DISP_FUNCTION_ID(Cactive_pluginCtrl, "Plugin_Interface", dispidPlugin_Interface, Plugin_Interface, VT_BSTR, VTS_I4 VTS_BSTR)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(Cactive_pluginCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(Cactive_pluginCtrl, 1)
	PROPPAGEID(Cactive_pluginPropPage::guid)
END_PROPPAGEIDS(Cactive_pluginCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(Cactive_pluginCtrl, "ACTIVE_PLUGIN.active_pluginCtrl.1",
	0x50d171ae, 0x536, 0x4fb6, 0xbb, 0x9d, 0x6c, 0x7e, 0xdd, 0xf0, 0x20, 0x6b)



// Type library ID and version

IMPLEMENT_OLETYPELIB(Cactive_pluginCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_Dactive_plugin =
		{ 0xEE693F3B, 0x1B36, 0x422B, { 0xA1, 0x18, 0xA6, 0x4A, 0xC2, 0xFA, 0xC, 0xF2 } };
const IID BASED_CODE IID_Dactive_pluginEvents =
		{ 0x97F111A3, 0x770F, 0x4A79, { 0xA2, 0xB4, 0x46, 0x49, 0x88, 0x84, 0x6A, 0xC3 } };



// Control type information

static const DWORD BASED_CODE _dwactive_pluginOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(Cactive_pluginCtrl, IDS_ACTIVE_PLUGIN, _dwactive_pluginOleMisc)



// Cactive_pluginCtrl::Cactive_pluginCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for Cactive_pluginCtrl

BOOL Cactive_pluginCtrl::Cactive_pluginCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ACTIVE_PLUGIN,
			IDB_ACTIVE_PLUGIN,
			afxRegApartmentThreading,
			_dwactive_pluginOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

// Cactive_pluginCtrl::Cactive_pluginCtrl - Constructor
Cactive_pluginCtrl::Cactive_pluginCtrl()
{
	InitializeIIDs(&IID_Dactive_plugin, &IID_Dactive_pluginEvents);
	// TODO: Initialize your control's instance data here.
	m_pl_ctrl = new CPlCtrl();
}

// Cactive_pluginCtrl::~Cactive_pluginCtrl - Destructor
Cactive_pluginCtrl::~Cactive_pluginCtrl()
{
	// TODO: Cleanup your control's instance data here.
	if (m_pl_ctrl)
	{
		delete ((CPlCtrl *)m_pl_ctrl);
		m_pl_ctrl = NULL;
	}
}

// Cactive_pluginCtrl::OnDraw - Drawing function
void Cactive_pluginCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
}

// Cactive_pluginCtrl::DoPropExchange - Persistence support
void Cactive_pluginCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// Cactive_pluginCtrl::OnResetState - Reset control to default state

void Cactive_pluginCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// Cactive_pluginCtrl message handlers
BSTR Cactive_pluginCtrl::Plugin_Interface(LONG l, BSTR p)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	CString  strmac;
	strmac="12345123451234512345";
	return strmac.AllocSysString();
}

BSTR Cactive_pluginCtrl::SetWorkModel(char * js_workmodel)
{
	BSTR pRet = NULL;
	if(((CPlCtrl *)m_pl_ctrl)->InitDisPlay(m_hWnd, js_workmodel))
		pRet = SetRetValue("{\"rst\":0}");
	else
		pRet = SetRetValue("{\"rst\":1}");

	return pRet;
}

BSTR Cactive_pluginCtrl::Play(char *js_playInfo)
{
	BSTR pRet = NULL;
	//((CPlCtrl *)m_pl_ctrl)->RegisterCallBack(OnEvent, this);
	if (((CPlCtrl *)m_pl_ctrl)->Play(js_playInfo))
		pRet = SetRetValue("{\"rst\":0}");
	else	
		pRet = SetRetValue("{\"rst\":1}");

	return pRet;
}

BSTR Cactive_pluginCtrl::ChangeLayout(char *js_layout)
{
	BSTR pRet = NULL;
	if (((CPlCtrl *)m_pl_ctrl)->SetLayout(js_layout))
		pRet = SetRetValue("{\"rst\":0}");

	return pRet;
}

BSTR Cactive_pluginCtrl::ChangePath(char *js_path)
{
	BSTR pRet = NULL;
	if (((CPlCtrl *)m_pl_ctrl)->SetPath(js_path))
		pRet = SetRetValue("{\"rst\":0}");

	return pRet;
}

BSTR Cactive_pluginCtrl::SetLayout()
{
	BSTR pRet = NULL;
	((CPlCtrl *)m_pl_ctrl)->SetLayout();
	return pRet;
}

BSTR Cactive_pluginCtrl::StopAllPlay()
{
	BSTR pRet = NULL;
	if (((CPlCtrl *)m_pl_ctrl)->StopAll())
		pRet = SetRetValue("{\"rst\":0}");
	else
		pRet = SetRetValue("{\"rst\":101}");

	return pRet;
}

BSTR Cactive_pluginCtrl::VodPlayJump(char *js_time)
{
	BSTR pRet = NULL;
	if (((CPlCtrl *)m_pl_ctrl)->VodStreamJump(js_time))
		pRet = SetRetValue("{\"rst\":0}");
	else
		pRet = SetRetValue("{\"rst\":4}");

	return pRet;
}

BSTR Cactive_pluginCtrl::GetWndParm(int nType)
{
	BSTR pRet = NULL;
	char info[1024] = {0};
	if (((CPlCtrl *)m_pl_ctrl)->GetWndParm(info,nType))
		pRet = SetRetValue(info);

	return pRet;
}

BSTR Cactive_pluginCtrl::SleepPlayer(bool bSleep)
{
	BSTR pRet = NULL;
	((CPlCtrl *)m_pl_ctrl)->SleepPlayer(bSleep);
	pRet = SetRetValue("{\"rst\":0}");

	return pRet;
}

BSTR Cactive_pluginCtrl::SetRetValue(char *psz_ret)
{
	CString  strmac(psz_ret);
	return strmac.AllocSysString();
}