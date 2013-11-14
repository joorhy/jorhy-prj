// active_pluginPropPage.cpp : Implementation of the Cactive_pluginPropPage property page class.

#include "stdafx.h"
#include "active_plugin.h"
#include "active_pluginPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(Cactive_pluginPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(Cactive_pluginPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(Cactive_pluginPropPage, "ACTIVE_PLUGIN.active_pluginPropPage.1",
	0xcda5b896, 0x378b, 0x4980, 0x81, 0x54, 0x7e, 0xf6, 0xe4, 0x5d, 0x88, 0xfc)



// Cactive_pluginPropPage::Cactive_pluginPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for Cactive_pluginPropPage

BOOL Cactive_pluginPropPage::Cactive_pluginPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVE_PLUGIN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// Cactive_pluginPropPage::Cactive_pluginPropPage - Constructor

Cactive_pluginPropPage::Cactive_pluginPropPage() :
	COlePropertyPage(IDD, IDS_ACTIVE_PLUGIN_PPG_CAPTION)
{
}



// Cactive_pluginPropPage::DoDataExchange - Moves data between page and properties

void Cactive_pluginPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// Cactive_pluginPropPage message handlers
