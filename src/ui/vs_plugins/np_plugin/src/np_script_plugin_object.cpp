#include "np_script_plugin_object.h"
#include "npfunctions.h"
#include "np_plugin.h"
#include "pl_type.h"
#include <string>

ScriptablePluginObject::ScriptablePluginObject(NPP npp) : ScriptablePluginObjectBase(npp)
{
	m_bCbReturn = 0;
	m_CallBkPtz	= NULL;
	m_CallBkState = NULL;
	m_CallBkVod = NULL;
}

ScriptablePluginObject::~ScriptablePluginObject()
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

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
	return (name == NPN_GetStringIdentifier("Plugin_Interface") ||
			name == NPN_GetStringIdentifier("ResgisterFunction") || 
			name == NPN_GetStringIdentifier("logMessage"));
}

bool ScriptablePluginObject::HasProperty(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
	return true;
}

bool  ScriptablePluginObject::SetProperty(NPIdentifier name, const NPVariant *value)
{
	return true;
}

bool ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)  
{  
	//if (InterlockedExchangeAdd(&m_bCbReturn, 0) > 0)
	if (m_bCbReturn > 0)
	{
		char *tmp = (char*)NPN_MemAlloc(strlen("{\"rst\":1}")+1);
		strncpy(tmp, "{\"rst\":1}", strlen("{\"rst\":1}"));
		tmp[strlen("{\"rst\":1}")] = '\0';
		STRINGZ_TO_NPVARIANT(tmp, *result);
		return true;
	}
	CNPPlugin * pPlugin = (CNPPlugin *)mNpp->pdata;
	//InterlockedExchangeAdd(&m_bCbReturn, 1);
	m_bCbReturn = 1;
	if(name == NPN_GetStringIdentifier("Plugin_Interface"))
	{
		int	cmd			= (int)NPVARIANT_TO_DOUBLE(args[0]);
		char *js_parm	= NULL;
		switch (cmd)
		{
		case 1:case 2:case 5:case 21:case 23:case 11:
			{
				NPString jsonStr= NPVARIANT_TO_STRING(args[1]);
				js_parm		= new char[jsonStr.UTF8Length + 1];
				memcpy(js_parm,jsonStr.UTF8Characters,jsonStr.UTF8Length);
				js_parm[jsonStr.UTF8Length] = '\0';
			}
			break;
		}
		switch(cmd)
		{
		case 1:		//设置工作模式和布局
			pPlugin->SetWorkModel(js_parm,result);
			break;
		case 2:		//改变布局
			pPlugin->ChangeLayout(js_parm,result);
			break;
		case 5:		//改变存储路径
			pPlugin->ChangePath(js_parm,result);
			break;
		case 21:	//打开历史流
			pPlugin->Play(js_parm,result);
			break;
		case 23:	//历史流跳转
			pPlugin->VodPlayJump(js_parm,result);
			break;
		case 11:	//播放实时视频
			pPlugin->Play(js_parm,result);
			break;

		case 3:		//得到当前焦点播放窗口参数
			pPlugin->GetWndParm(FOCUS_WINDOW, result);
			break;
		case 4:		//得到所有窗口播放参数列表
			pPlugin->GetWndParm(ALL_WINDOW, result);
			break;
		case 12:	//关闭所有播放
			pPlugin->StopAllPlay(result);
			break;
		case 22:	//关闭所有历史流
			pPlugin->StopAllPlay(result);
			break;
		case 30:	//播放器sleep
			pPlugin->SleepPlayer((bool)NPVARIANT_TO_BOOLEAN(args[1]),result);
			break;
		default:
			break;
		}
		if (js_parm)
			delete js_parm;
	}

	if(name == NPN_GetStringIdentifier("ResgisterFunction"))
	{
		switch((int)NPVARIANT_TO_DOUBLE(args[1]))
		{
		case CALLBACK_PTZCTL:
			m_CallBkPtz	= NPVARIANT_TO_OBJECT(args[0]);
			NPN_RetainObject(m_CallBkPtz);
			break;

		case CALLBACK_ONSTATE:
			m_CallBkState = NPVARIANT_TO_OBJECT(args[0]);
			NPN_RetainObject(m_CallBkState);
			break;

		case CALLBACK_ONVOD:
			m_CallBkVod = NPVARIANT_TO_OBJECT(args[0]);
			NPN_RetainObject(m_CallBkVod);
			break;
		default:
			break;
		}
	}
	//InterlockedExchangeAdd(&m_bCbReturn, -1);
	m_bCbReturn = 0;
	return true;  
}  

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	//if (InterlockedExchangeAdd(&m_bCbReturn, 0) > 0)
	if (m_bCbReturn > 0)
	{
		char *tmp = (char*)NPN_MemAlloc(strlen("{\"rst\":1}")+1);
		strncpy(tmp, "{\"rst\":1}", strlen("{\"rst\":1}"));
		tmp[strlen("{\"rst\":1}")] = '\0';
		STRINGZ_TO_NPVARIANT(tmp, *result);
		return true;
	}
	//InterlockedExchangeAdd(&m_bCbReturn, 1);
	m_bCbReturn = 1;
	int nType = NPVARIANT_TO_INT32(args[0]);
	switch (nType)
	{
	case CALLBACK_PTZCTL:
		if (m_CallBkPtz != NULL)
			NPN_InvokeDefault(mNpp, m_CallBkPtz, args+1, argCount-1, result);
		break;
	case CALLBACK_ONSTATE:
		if (m_CallBkState != NULL)
			NPN_InvokeDefault(mNpp, m_CallBkState, args+1, argCount-1, result);
		break;
	case CALLBACK_ONVOD:
		if (m_CallBkVod != NULL)
			NPN_InvokeDefault(mNpp, m_CallBkVod, args+1, argCount-1, result);
		break;
	default:
		break;
	}
	m_bCbReturn = 0;
	//InterlockedExchangeAdd(&m_bCbReturn, -1);
	return true;
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

	return true;
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
	BOOLEAN_TO_NPVARIANT(true, rvalFlag);
	NPN_SetProperty(mNpp, pWindowObj, iSetHandle_id, &rvalFlag);

	return true;
}
