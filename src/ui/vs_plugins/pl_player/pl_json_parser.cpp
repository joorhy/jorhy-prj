#include "stdafx.h"
#include "pl_json_parser.h"
#include "json.h"

PlJsonParser::PlJsonParser()
{

}

PlJsonParser::~PlJsonParser()
{

}

BOOL PlJsonParser::ParserLayout(const char *pJsStr, PL_LayoutInfo &layoutInfo)
{
	json_object *layout_obj = json_tokener_parse((char *)pJsStr);
	if(is_error(layout_obj))
		return FALSE;

	memset(&layoutInfo, 0, sizeof(PL_LayoutInfo));
	layoutInfo.nMod			= json_object_get_int(json_object_object_get(layout_obj, "mod")) - 1;
	layoutInfo.nLayout		= json_object_get_int(json_object_object_get(layout_obj, "layout"));
	layoutInfo.nWindows	= json_object_get_int(json_object_object_get(layout_obj, "windows"));
	layoutInfo.nMax			= json_object_get_int(json_object_object_get(layout_obj, "max"));
	layoutInfo.nUid				= json_object_get_int(json_object_object_get(layout_obj, "uid"));

	char *tmpstr = json_object_get_string(json_object_object_get(layout_obj, "imgPath"));
	if(tmpstr)
		strcpy(layoutInfo.imgPath, tmpstr);
	tmpstr = json_object_get_string(json_object_object_get(layout_obj, "videoPath"));
	if(tmpstr)
		strcpy(layoutInfo.mediaPath, tmpstr);
	json_object_put(layout_obj);

	return TRUE;
}

BOOL PlJsonParser::ParserLayout2(const char *pJsStr, PL_LayoutInfo &layoutInfo)
{
	json_object *layout_obj = json_tokener_parse((char *)pJsStr);
	if(is_error(layout_obj))
		return FALSE;

	memset(&layoutInfo, 0, sizeof(PL_LayoutInfo));
	layoutInfo.nLayout		= json_object_get_int(json_object_object_get(layout_obj, "layout"));
	layoutInfo.nWindows	= json_object_get_int(json_object_object_get(layout_obj, "windows"));
	layoutInfo.nMax			= json_object_get_int(json_object_object_get(layout_obj, "max"));

	json_object_put(layout_obj);

	return TRUE;
}

BOOL PlJsonParser::ParserPlay(const char *pJsStr, PL_PlayInfo &playInfo)
{
	json_object *play_obj = NULL;
	play_obj = json_tokener_parse((char *)pJsStr);
	if(is_error(play_obj))
		return FALSE;
	
	memset(&playInfo, 0, sizeof(PL_PlayInfo));
	playInfo.nId = json_object_get_int(json_object_object_get(play_obj, "id"));
	strcpy(playInfo.strIpaddr, json_object_get_string(json_object_object_get(play_obj, "ip")));
	playInfo.nPort = json_object_get_int(json_object_object_get(play_obj, "port"));
	strcpy(playInfo.strResid, json_object_get_string(json_object_object_get(play_obj,"resid")));
	//实时视频
	json_object *real_obj = json_object_object_get(play_obj, "ms");
	if (!is_error(play_obj))
	{
		playInfo.nSubStreamType = 	json_object_get_int(real_obj);
		playInfo.nPlayMode = STREAME_REALTIME;
	}
	//历史视频
	else
	{
		playInfo.nStartTime = json_object_get_int(json_object_object_get(play_obj, "start"));
		playInfo.nEndTime = json_object_get_int(json_object_object_get(play_obj, "end"));
		playInfo.nPlayMode = STREAME_FILE;
	}
	playInfo.nStreamType = VLC_VIDEO;
	json_object_put(real_obj);
	json_object_put(play_obj);

	return TRUE;
}

BOOL PlJsonParser::MakeWndParam(const PL_PlayInfo &playInfo, char *pJsStr)
{
	json_object *retInfo = json_object_new_object();
	json_object_object_add(retInfo,"id", json_object_new_int(playInfo.nId));
	json_object_object_add(retInfo,"resid", json_object_new_string((char *)playInfo.strResid));
	json_object_object_add(retInfo,"ms", json_object_new_int(playInfo.nSubStreamType));
	strcpy(pJsStr, json_object_to_json_string(retInfo));
	json_object_put(retInfo);

	return TRUE;
}

BOOL PlJsonParser::MakeAllWndParam(char **pVecStr, int nWndNum, char *pJsStr)
{
	json_object *allInfo = NULL;
	json_object *tmp	= NULL;
	
	allInfo = json_object_new_array();
	for(int i=0; i<nWndNum; ++i)
	{
		tmp = json_tokener_parse(pVecStr[i]);
		if(is_error(tmp))
			continue;
		
		json_object_array_add(allInfo, tmp);
	}
	sprintf(pJsStr, "%s", json_object_to_json_string(allInfo));
	json_object_put(allInfo);

	return TRUE;
}

BOOL PlJsonParser::MakeCbStatus(const PL_PlayInfo &playInfo, char *pJsStr)
{
	json_object *j_obj = json_object_new_object();
	json_object_object_add(j_obj,"id", json_object_new_int(playInfo.nId));
	json_object_object_add(j_obj, "state", json_object_new_int(1));
	strcpy(pJsStr, json_object_to_json_string(j_obj));
	json_object_put(j_obj);

	return TRUE;
}

BOOL PlJsonParser::MakeFocus(const PL_PlayInfo &playInfo, char *pJsStr)
{
	json_object *js_args	= NULL;
	js_args = json_object_new_object();
	json_object_object_add(js_args, "id", json_object_new_int(playInfo.nId));
	json_object_object_add(js_args, "resid", json_object_new_string((char *)playInfo.strResid));
	json_object_object_add(js_args, "ms", json_object_new_int(playInfo.nSubStreamType));
	strcpy(pJsStr, json_object_to_json_string(js_args));
	json_object_put(js_args);

	return TRUE;
}