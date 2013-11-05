#include "JoParser.h"

const char *flag_begin = "start=";
const char *flag_end = "end=";

/*j_result_t CJoParser::ParseUrl(char *psz_mrl, j_pl_cfg_t &OUT_cfg)
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
		return J_PL_ERROR_MRL;

	beg = end;
	beg += 1;
	end = strchr(beg,'/');
	char *port = new char[end - beg];
	strncpy(port,beg,end - beg);
	OUT_cfg.i_port	= atoi(port);
	delete port;

	beg = end;
	beg += 1;
	end = strchr(beg,'?');
	if (end != NULL)
	{
		strncpy(OUT_cfg.psz_resource,beg,end-beg);

		beg = strstr(beg, flag_begin);
		if (beg != NULL)
			OUT_cfg.begin_time = atoi(beg + strlen(flag_begin));

		beg = strstr(beg, flag_end);
		if (beg != NULL)
			OUT_cfg.end_time = atoi(beg + strlen(flag_end));
	}
	else
	{
		end = strchr(beg,'\0');
		strncpy(OUT_cfg.psz_resource,beg,end-beg);
	}


	return J_PL_NO_ERROR;
}*/
#ifndef WIN32
int strnicmp(const char *dst, const char *src, int count)
{
	int ch1, ch2;
	do 
	{
		if (((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <='Z'))
			ch1 += 0x20;
		if (((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <='Z'))
			ch2 += 0x20;
	} while (--count && ch1 && (ch1 == ch2));
	
	return (ch1 - ch2);
}
#endif

j_result_t CJoParser::ParsePicture(char *psz_filename, int &outType)
{
	if(!psz_filename)
		return J_PARAM_ERROR;

	char *pos = strrchr(psz_filename,'.');
	pos++;
	int len = strlen(psz_filename) - (pos - psz_filename) - 1;
	if(len > 0)
	{
		if(strnicmp(pos,"png",len) == 0)
		{
			outType = jo_png;
		}
		else if(strnicmp(pos,"jpeg",len) == 0  || strnicmp(pos,"jpg",len) == 0)
		{
			outType = jo_jpeg;
		}
		/*
		add here
		*/
		else
		{
			outType = jo_png;
		}
	}
	else
		outType = jo_jpeg;

	return J_OK;
}