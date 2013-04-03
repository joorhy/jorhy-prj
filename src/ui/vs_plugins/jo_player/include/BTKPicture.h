#pragma once
#include "BTKBase.h"
#include "DataStruct.h"
extern "C"
{
#include "libavcodec\avcodec.h"
};

class BTKPicture : public BTKBase
{
public:
	//auto parse picture type
	static BTK_RESULT SavePicture(btk_video_format_t &ft,const char *data,btk_video_out_t &vt,char *filename);

	static BTK_RESULT SavePNG(btk_video_format_t &ft,const char *data,btk_video_out_t &vt,char *filename);
	static BTK_RESULT SaveJPEG(btk_video_format_t &ft,const char *data,btk_video_out_t &vt,char *filename);

private:
	static BTK_RESULT YUV2RGB24(AVPicture &src,AVPicture &dst,btk_video_out_t &vt);
	static BTK_RESULT WritePNG(AVPicture &src,btk_video_out_t &vt,char *filename);
	static BTK_RESULT FillYuv(AVPicture &src,btk_video_out_t &vt,const char *data);
};
