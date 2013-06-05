#pragma once

#include "plugin_base.h"

class ScriptablePluginObject : public ScriptablePluginObjectBase
{
public:
	ScriptablePluginObject(NPP npp) : ScriptablePluginObjectBase(npp)
	{

	}

	virtual bool HasMethod(NPIdentifier name);
	virtual bool HasProperty(NPIdentifier name);
	virtual bool GetProperty(NPIdentifier name, NPVariant *result);
	virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
	virtual bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);

private:
	bool GetProperty(const char *pType, NPVariant *result);
	bool SetProperty(const char *pType, const NPVariant *value);
};

//static NPObject *AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
//{
//	NPObject *p = new ScriptablePluginObject(npp);
//	return p;
//}
//
//DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject, AllocateScriptablePluginObject);
