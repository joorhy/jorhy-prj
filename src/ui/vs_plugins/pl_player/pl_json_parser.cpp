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
	layoutInfo.nMod			= json_object_get_int(json_object_object_get(layout_obj, "mod"));
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