#pragma once

// active_pluginPropPage.h : Declaration of the Cactive_pluginPropPage property page class.


// Cactive_pluginPropPage : See active_pluginPropPage.cpp for implementation.

class Cactive_pluginPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(Cactive_pluginPropPage)
	DECLARE_OLECREATE_EX(Cactive_pluginPropPage)

// Constructor
public:
	Cactive_pluginPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_ACTIVE_PLUGIN };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

