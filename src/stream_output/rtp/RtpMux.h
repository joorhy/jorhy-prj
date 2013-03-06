#ifndef __RTPMUX_H_
#define __RTPMUX_H_
#include "j_includes.h"
#include "x_time.h"
#include "x_module_manager_def.h"

class CRtpMux;
class rtp_helper
{
friend class CRtpMux;
public:
	rtp_helper();
	~rtp_helper();

protected:
	int get_rtp_head(char *head, int i_length, int payload_type, uint64_t timeStamp, bool is_video, bool is_mark);

public:
	typedef struct rtp_head_s
	{
		unsigned short rtsp_head;
		unsigned short length;

		char csrc_count:4;
		char x:1;
		char p:1;
		char vertion:2;

		char payload_type:7;
		char m:1;

		unsigned short seq;
		unsigned int timestamp;
		unsigned int ssrc;
	} rtp_head_t;

	int m_video_seq_num;
	int m_audio_seq_num;
	int m_video_time;
	int m_audio_time;
	int m_video_time_inc;
	int m_audio_time_inc;
	unsigned int m_video_ssrc;
	unsigned int m_audio_ssrc;
};

class CRtpMux : public J_MuxFilter
{
public:
	CRtpMux();
	~CRtpMux();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CRtpMux();
		return J_OK;
	}

public:
	virtual int Init();
	virtual void Deinit();
	virtual int Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata = 0);

private:
	int PrepareAudioData(const char *pData, int nLen, uint64_t timeStamp, char *pOutputData, int &nOutLen);
	int PrepareVideoData(const char *pData, int nLen, uint64_t timeStamp, char *pOutputData, int &nOutLen);

protected:
	typedef struct  nalu_header_s
	{
		//byte 0
		unsigned char TYPE:5;
		unsigned char NRI:2;
		unsigned char F:1;
	} nalu_header_t; /**//* 1 BYTES */

	typedef struct fu_indicator_s
	{
		//byte 0
		unsigned char TYPE:5;
		unsigned char NRI:2;
		unsigned char F:1;
	} fu_indicator_t; /**//* 1 BYTES */

	typedef struct fu_header_s
	{
		//byte 0
		unsigned char TYPE:5;
		unsigned char R:1;
		unsigned char E:1;
		unsigned char S:1;
	} fu_header_t; /**//* 1 BYTES */

private:
	rtp_helper helper;
};

MUX_BEGIN_MAKER(rtp)
	MUX_ENTER_MAKER("rtp", CRtpMux::Maker)
MUX_END_MAKER()

#endif //~__RTPMUX_H_
