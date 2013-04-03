#include "plugin_object.h"
#include "npupp.h"
#include "NPPluginMisc.h"
#include <string>

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
	return (name == NPN_GetStringIdentifier("SelectFolder"));
}

bool ScriptablePluginObject::HasProperty(NPIdentifier name)
{
	return PR_FALSE;
}

bool ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
	return PR_TRUE;
}

bool  ScriptablePluginObject::SetProperty(NPIdentifier name, const NPVariant *value)
{
	return PR_TRUE;
}

bool ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)  
{  
	CNPPluginMisc * pPlugin = (CNPPluginMisc *)mNpp->pdata;
	bool bRet = PR_FALSE;

	if(name == NPN_GetStringIdentifier("SelectFolder"))
	{
		bRet = pPlugin->SelectFolder(result);
	}
	return bRet;  
}  

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return PR_TRUE;
}

bool ScriptablePluginObject::GetProperty(const char *pType, NPVariant *result)
{
	NPObject *pWindowObj = NULL;
	NPN_GetValue(mNpp, NPNVWindowNPObject, &pWindowObj);
	CHAR strObj[8] = {0};
	sprintf(strObj, "%x", mNpp);

	CHAR strNPId[32] = {0};
	sprintf(strNPId, "%s%s", strObj, pType);
	NPIdentifier iHandle_id = NPN_GetStringIdentifier(strNPId);
	NPN_GetProperty(mNpp, pWindowObj, iHandle_id,  result);

	return PR_TRUE;
}

bool ScriptablePluginObject::SetProperty(const char *pType, const NPVariant *value)
{
	NPObject *pWindowObj = NULL;
	NPN_GetValue(mNpp, NPNVWindowNPObject, &pWindowObj);
	CHAR strObj[8] = {0};
	sprintf(strObj, "%x", mNpp);

	CHAR strNPId[32] = {0};
	sprintf(strNPId, "%s%s", strObj, pType);
	NPIdentifier iHandle_id = NPN_GetStringIdentifier(strNPId);
	NPN_SetProperty(mNpp, pWindowObj, iHandle_id, value);

	memset(strNPId, 0, sizeof(strNPId));
	sprintf(strNPId, "%sSet%s", strObj, pType);
	NPIdentifier iSetHandle_id = NPN_GetStringIdentifier(strNPId);

	NPVariant rvalFlag;
	BOOLEAN_TO_NPVARIANT(PR_TRUE, rvalFlag);
	NPN_SetProperty(mNpp, pWindowObj, iSetHandle_id, &rvalFlag);

	return PR_TRUE;
}
