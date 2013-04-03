#pragma once
#include "btkbase.h"
#include "DataStruct.h"

class BTKParser : public BTKBase
{
public:
	static BTK_RESULT ParseUrl(char *psz_mrl,btk_cfg_t &OUT_cfg);
	static BTK_RESULT ParsePicture(char *psz_filename,int &outType);		//Ïê¼ûbtk_picture_type_e
};
