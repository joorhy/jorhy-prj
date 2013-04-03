#ifndef __NP_CONSTRUCTABLE_PLUGIN_H_
#define __NP_CONSTRUCTABLE_PLUGIN_H_
#include "npupp.h"
#include "np_script_plugin_base.h"

class ConstructablePluginObject : public ScriptablePluginObjectBase
{
public:
	ConstructablePluginObject(NPP npp) : ScriptablePluginObjectBase(npp)
	{
	}

	virtual bool Construct(const NPVariant *args, uint32_t argCount, NPVariant *result);
};

static NPObject * AllocateConstructablePluginObject(NPP npp, NPClass *aClass)
{
	return new ConstructablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ConstructablePluginObject, AllocateConstructablePluginObject);

#endif //~__NP_CONSTRUCTABLE_PLUGIN_H_