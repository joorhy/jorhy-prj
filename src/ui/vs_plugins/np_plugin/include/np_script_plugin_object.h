#ifndef __NP_SCRIPT_PLUGIN_OBJECT_H_
#define __NP_SCRIPT_PLUGIN_OBJECT_H_
#include "np_script_plugin_base.h"

class ScriptablePluginObject : public ScriptablePluginObjectBase
{
public:
	ScriptablePluginObject(NPP npp);
	~ScriptablePluginObject();

	virtual bool HasMethod(NPIdentifier name);
	virtual bool HasProperty(NPIdentifier name);
	virtual bool GetProperty(NPIdentifier name, NPVariant *result);
	virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
	virtual bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);

private:
	bool GetProperty(const char *pType, NPVariant *result);
	bool SetProperty(const char *pType, const NPVariant *value);

	NPObject *m_CallBkPtz;
	NPObject *m_CallBkState;
	NPObject *m_CallBkVod;
	long volatile m_bCbReturn;
	DWORD m_lastInvokeTime;
};

static NPObject *AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
{
	return new ScriptablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject, AllocateScriptablePluginObject);

#endif //__NP_SCRIPT_PLUGIN_OBJECT_H_