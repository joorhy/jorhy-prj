#pragma once
#include "x_pl_base.h"
#include "x_pl_data_struct.h"

class J_PlParser : public J_PlBase
{
public:
	static J_PL_RESULT ParseUrl(char *psz_mrl,j_pl_cfg_t &OUT_cfg);
	static J_PL_RESULT ParsePicture(char *psz_filename,int &outType);		//Ïê¼ûbtk_picture_type_e
};
