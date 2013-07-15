#ifndef __JOPARSER_H_
#define __JOPARSER_H_
#include "j_includes.h"

class CJoParser
{
public:
	//static j_result_t ParseUrl(char *psz_mrl,j_pl_cfg_t &OUT_cfg);
	static j_result_t ParsePicture(char *psz_filename,int &outType);		//Ïê¼ûbtk_picture_type_e
};

#endif //~__JOPARSER_H_