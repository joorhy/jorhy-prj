#include "np_script_plugin_object.h"
#include "npupp.h"
#include "np_plugin.h"
#include <string>

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
	return (name == NPN_GetStringIdentifier("Plugin_Interface") ||
			name == NPN_GetStringIdentifier("ResgisterFunction") || 
			name == NPN_GetStringIdentifier("logMessage"));
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
	CNPPlugin * pPlugin = (CNPPlugin *)mNpp->pdata;
	bool bRet = PR_FALSE;

	if(name == NPN_GetStringIdentifier("Plugin_Interface"))
	{
		int	cmd			= (int)NPVARIANT_TO_DOUBLE(args[0]);
		NPString jsonStr= NPVARIANT_TO_STRING(args[1]);
		char *js_parm		= new char[jsonStr.utf8length + 1];

		memcpy(js_parm,jsonStr.utf8characters,jsonStr.utf8length);
		js_parm[jsonStr.utf8length] = '\0';
		switch(cmd)
		{
		case 1:		//设置工作模式和布局
			bRet = pPlugin->SetWorkModel(js_parm,result);
			break;

		case 2:		//改变布局
			bRet = pPlugin->SetLayout(js_parm,result);
			break;

		case 3:		//得到当前焦点播放窗口参数
			bRet = pPlugin->GetWndParm(FOCUS_WINDOW,result);
			break;

		case 4:		//得到所有窗口播放参数列表
			bRet = pPlugin->GetWndParm(ALL_WINDOW,result);
			break;

		case 11:	//播放实时视频
			bRet = pPlugin->Play(js_parm,result);
			break;

		case 12:	//关闭所有播放
			bRet = pPlugin->StopAllPlay(result);
			break;

		case 21:	//打开历史流
			bRet = pPlugin->Play(js_parm,result);
			break;

		case 22:	//关闭所有历史流
			bRet = pPlugin->StopAllPlay(result);
			break;

		case 23:	//历史流跳转
			bRet = pPlugin->VodPlayJump(js_parm,result);
			break;

		case 30:	//播放器sleep
			bRet = pPlugin->SleepPlayer((bool)NPVARIANT_TO_BOOLEAN(args[1]),result);
			break;

		default:
			break;
		}
		delete [] js_parm;
	}

	if(name == NPN_GetStringIdentifier("ResgisterFunction"))
	{
		int type = (int)NPVARIANT_TO_DOUBLE(args[1]);

		pPlugin->RegisterCallBack(NPVARIANT_TO_OBJECT(args[0]),type);
		return PR_TRUE;

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
