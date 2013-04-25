#pragma once
#include "x_pl_base.h"
#include "x_pl_data_struct.h"
extern "C"
{
#include "libavcodec\avcodec.h"
};

class CXPlPicture : public J_PlBase
{
public:
	//auto parse picture type
	static J_PL_RESULT SavePicture(j_pl_video_format_t &ft,const char *data,j_pl_video_out_t &vt,char *filename);

	static J_PL_RESULT SavePNG(j_pl_video_format_t &ft,const char *data,j_pl_video_out_t &vt,char *filename);
	static J_PL_RESULT SaveJPEG(j_pl_video_format_t &ft,const char *data,j_pl_video_out_t &vt,char *filename);

private:
	static J_PL_RESULT YUV2RGB24(AVPicture &src,AVPicture &dst,j_pl_video_out_t &vt);
	static J_PL_RESULT WritePNG(AVPicture &src,j_pl_video_out_t &vt,char *filename);
	static J_PL_RESULT FillYuv(AVPicture &src,j_pl_video_out_t &vt,const char *data);
};
