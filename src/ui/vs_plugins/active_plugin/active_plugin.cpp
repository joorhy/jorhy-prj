// active_plugin.cpp : Implementation of Cactive_pluginApp and DLL registration.

#include "stdafx.h"
#include "active_plugin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Cactive_pluginApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xBFB3815B, 0xC1D5, 0x4E82, { 0x9C, 0x1F, 0xCF, 0x58, 0x33, 0xB, 0x42, 0x17 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// Cactive_pluginApp::InitInstance - DLL initialization

BOOL Cactive_pluginApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// Cactive_pluginApp::ExitInstance - DLL termination

int Cactive_pluginApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
