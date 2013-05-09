#include "x_pl_picture.h"
#include "x_pl_parser.h"
#include "x_pl_error.h"
#include "x_pl_log.h"
#include "png.h"
extern "C"
{
#include "libswscale\swscale.h"
};

J_PL_RESULT CXPlPicture::SavePicture(j_pl_video_format_t &ft,const char *data,j_pl_video_out_t &vt,char *filename)
{
	int ptype;
	J_PL_RESULT br;

	br = J_PlParser::ParsePicture(filename,ptype);
	if(br != J_PL_NO_ERROR)
		return br;

	switch(ptype)
	{
	case J_PL_PNG:
		br = SavePNG(ft,data,vt,filename);
		break;

	case J_PL_JPEG:
		br = SaveJPEG(ft,data,vt,filename);
		break;

	default:
		return J_PL_ERROR_PICTURE_SUPPORT;
	}

	return br;
}

J_PL_RESULT CXPlPicture::SavePNG(j_pl_video_format_t &ft,const char *data,j_pl_video_out_t &vt,char *filename)
{
	J_PL_RESULT br;
	AVPicture src,dst;

	memset(&src,0,sizeof(AVPicture));
	memset(&dst,0,sizeof(AVPicture));
	br = FillYuv(src,vt,data);
	if(br != J_PL_NO_ERROR)
		return br;

	if(av_image_alloc(dst.data,dst.linesize,vt.width,vt.height,PIX_FMT_RGBA,1) < 0)
	{
		br = J_PL_ERROR_UNKNOW;
		goto SavePNG_Error;
	}

	br = YUV2RGB32(src,dst,vt);
	if(br != J_PL_NO_ERROR)
		goto SavePNG_Error;

	br = WritePNG(dst,vt,filename);
	if(br != J_PL_NO_ERROR)
		goto SavePNG_Error;

	av_freep(&dst.data[0]);

	return J_PL_NO_ERROR;

SavePNG_Error:
	for(int i=0;i<4;i++)
	{
		if(dst.data[i])
			av_freep(&dst.data[i]);
	}
	return br;
}

J_PL_RESULT CXPlPicture::SaveJPEG(j_pl_video_format_t &ft,const char *data,j_pl_video_out_t &vt,char *filename)
{
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlPicture::YUV2RGB32(AVPicture &src,AVPicture &dst,j_pl_video_out_t &vt)
{
	SwsContext *sws_ctx = NULL;
	enum PixelFormat src_pix_fmt = PIX_FMT_NONE;
	enum PixelFormat dst_pix_fmt = PIX_FMT_RGBA;

	switch(vt.FourCCType)
	{
	case J_PL_CODEC_YV12: case J_PL_CODEC_RGB32:
		src_pix_fmt = PIX_FMT_YUV420P; 
		break;
	default:
		return J_PL_ERROR_PICTURE_SUPPORT;
	}

	sws_ctx = sws_getContext(vt.width, vt.height, src_pix_fmt,
							vt.width, vt.height, dst_pix_fmt,
							SWS_BILINEAR, NULL, NULL, NULL);
	if(!sws_ctx)
	{
		sws_freeContext(sws_ctx);
		return J_PL_ERROR_UNKNOW;
	}

	sws_scale(sws_ctx,
			(const uint8_t * const*)src.data,src.linesize,0,vt.height,
			dst.data, dst.linesize);

	sws_freeContext(sws_ctx);
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlPicture::WritePNG(AVPicture &src,j_pl_video_out_t &vt,char *filename)
{
	png_FILE_p fp			= NULL;
	png_structp write_ptr	= NULL;
	png_infop info_ptr		= NULL;
	png_bytep *row_pointers = NULL;
	png_colorp palette		= NULL;

	fp = fopen(filename, "wb");
	if(!fp)
	{
		j_pl_error("Could not open File %s\n",filename);
		return J_PL_ERROR_OPEN_FILE;
	}

	write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!write_ptr)
	{
		fclose(fp);
		return J_PL_ERROR_LIBPNG;
	}

	info_ptr = png_create_info_struct(write_ptr);
	if (info_ptr == NULL)
	{
		fclose(fp);
		return J_PL_ERROR_LIBPNG;
	}
	if (setjmp(png_jmpbuf(write_ptr)))
	{
		fclose(fp);
		return J_PL_ERROR_LIBPNG;
	}
	png_init_io(write_ptr, fp);

	png_set_IHDR(write_ptr, info_ptr, vt.width, vt.height, 8,			//8bitÎ»Éî¶È
				PNG_COLOR_TYPE_RGB_ALPHA,PNG_INTERLACE_NONE, 
				PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	palette = (png_colorp)png_malloc(write_ptr, PNG_MAX_PALETTE_LENGTH * png_sizeof(png_color));
	png_set_PLTE(write_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);

	png_write_info(write_ptr, info_ptr);

	png_set_packing(write_ptr);
	row_pointers = (png_bytep *)malloc(vt.height * sizeof(png_bytep));
	for(int i=0;i<vt.height;i++)
		row_pointers[i] = src.data[0] + src.linesize[0]*i;
	png_write_image(write_ptr, row_pointers);
	png_free(write_ptr, palette);
	free(row_pointers);
	fclose(fp);

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlPicture::FillYuv(AVPicture &src,j_pl_video_out_t &vt,const char *data)
{
	switch(vt.FourCCType)
	{
	case J_PL_CODEC_YV12: case J_PL_CODEC_RGB32:
		src.data[0]		= (uint8_t *)data;
		src.linesize[0] = vt.width;

		src.data[1]		= (uint8_t *)(data + vt.width * vt.height);
		src.linesize[1] = vt.width / 2;

		src.data[2]		= (uint8_t *)(data + vt.width * vt.height +
									(vt.width * vt.height / 4));
		src.linesize[2] = vt.width / 2;

		break;

	default:
		return J_PL_ERROR_PICTURE_SUPPORT;
	}

	return J_PL_NO_ERROR;
}