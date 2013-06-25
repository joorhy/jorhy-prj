#include "json.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

char url_buff[512];

char *GetMCUrl()
{
    FILE *fp = fopen("x_gse_conf.json", "rb");
    if (fp == NULL)
    {
        assert (false);
        return NULL;
    }

    char json_buff[1024] = {0};
    int read_len = fread(json_buff, 1, sizeof(json_buff), fp);
    json_object *helper = json_object_new_object();
	helper = json_tokener_parse((char *)json_buff);
	if(is_error(helper))
	{
	    assert(false);
		return NULL;
	}

	memset(url_buff, 0, 512);
	sprintf(url_buff, "http://%s:%d/controller/server",
        json_object_get_string(
            json_object_object_get(
                json_object_object_get(helper,(char *)"MCServer"), (char *)"mc_addr")),
        json_object_get_int(
            json_object_object_get(
                json_object_object_get(helper,(char *)"MCServer"), (char *)"mc_port")));

    fclose(fp);
    return url_buff;
}

char *GetSCDName()
{
    FILE *fp = fopen("x_gse_conf.json", "rb");
    if (fp == NULL)
    {
        assert (false);
        return NULL;
    }

    char json_buff[1024] = {0};
    int read_len = fread(json_buff, 1, sizeof(json_buff), fp);
    json_object *helper = json_object_new_object();
	helper = json_tokener_parse((char *)json_buff);
	if(is_error(helper))
	{
	    assert(false);
		return NULL;
	}

    memset(url_buff, 0, 512);
	sprintf(url_buff, "%s/%s",
        json_object_get_string(
            json_object_object_get(
                json_object_object_get(helper,(char *)"SCD"), (char *)"path")),
        json_object_get_string(
            json_object_object_get(
                json_object_object_get(helper,(char *)"SCD"), (char *)"name")));

    fclose(fp);

    return url_buff;
}
