#pragma once

#include "npupp.h"
#include "plugin_base.h"

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
