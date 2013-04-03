#include "..\include\BTKParser.h"
#include "..\include\BTKError.h"
#include <stdio.h>
#include <string>


BTK_RESULT BTKParser::ParseUrl(char *psz_mrl,btk_cfg_t &OUT_cfg)
{
	memset(&OUT_cfg,0,sizeof(OUT_cfg));
	char *beg = NULL;
	char *end = NULL;

	beg = psz_mrl;
	end = strchr(beg,':');
	char *proto = new char [end - beg];
	strncpy(proto,beg,end-beg);
	for(int i=0;btk_protocol_values[i].psz_name;i++)
	{
		if(strnicmp(proto,btk_protocol_values[i].psz_name,4) == 0)
		{
			OUT_cfg.i_protocol = btk_protocol_values[i].i_name;
			break;
		}
	}
	delete proto;

	beg = strstr(psz_mrl,"//");
	beg += strlen("//");
	end = strchr(beg,':');
	if(beg && end)
		strncpy(OUT_cfg.psz_ip,beg,end - beg);
	else
		return BTK_ERROR_MRL;

	beg = end;
	beg += 1;
	end = strchr(beg,'/');
	char *port = new char[end - beg];
	strncpy(port,beg,end - beg);
	OUT_cfg.i_port	= atoi(port);
	delete port;

	beg = end;
	beg += 1;
	end = strchr(beg,'\0');
	strncpy(OUT_cfg.psz_resource,beg,end-beg);

	return BTK_NO_ERROR;
}
BTK_RESULT BTKParser::ParsePicture(char *psz_filename,int &outType)
{
	if(!psz_filename)
		return BTK_ERROR_FILENAME;

	char *pos = strrchr(psz_filename,'.');
	pos++;
	int len = strlen(psz_filename) - (pos - psz_filename) - 1;
	if(len > 0)
	{
		if(strnicmp(pos,"png",len) == 0)
		{
			outType = BTK_PNG;
		}
		else if(strnicmp(pos,"jpeg",len) == 0  || strnicmp(pos,"jpg",len) == 0)
		{
			outType = BTK_JPEG;
		}
		/*
		add here
		*/
		else
		{
			outType = BTK_PNG;
		}
	}
	else
		outType = BTK_PNG;

	return BTK_NO_ERROR;
}