#ifndef __JOPICTURE_H_
#define __JOPICTURE_H_
#include "j_includes.h"
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavcore/imgutils.h"
}

class CJoPicture
{
public:
	//auto parse picture type
	static j_result_t SavePicture(J_VideoFormat &ft,const char *data,J_VideoDecodeParam &vt,char *filename);

	static j_result_t SavePNG(J_VideoFormat &ft,const char *data,J_VideoDecodeParam &vt,char *filename);
	static j_result_t SaveJPEG(J_VideoFormat &ft,const char *data,J_VideoDecodeParam &vt,char *filename);

	static j_result_t YUV2RGB32(AVPicture &src,AVPicture &dst,J_VideoDecodeParam &vt);
	static j_result_t FillYuv(AVPicture &src,J_VideoDecodeParam &vt,const char *data);
private:
	static j_result_t WritePNG(AVPicture &src,J_VideoDecodeParam &vt,char *filename);
};

#endif //~__JOPICTURE_H_