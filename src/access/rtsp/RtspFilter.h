#ifndef __RTSP_H_
#define __RTSP_H_
#include "j_includes.h"
#include "x_module_manager_def.h"

enum RTSP_METHORD
{
	RTSP_OPTIONS = 1,
	RTSP_DESCRIBE,
	RTSP_SETUP,
	RTSP_SETUP_UNSPORT,
	RTSP_PLAY,
	RTSP_PAUSE,
	RTSP_TEARDOWN
};

class CRtspFilter : public J_RequestFilter
				  , public J_VodCommandFilter
{
public:
	CRtspFilter();
	~CRtspFilter();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CRtspFilter();
		return J_OK;
	}

public:
	///J_ProtocolFilter
	virtual int Parser(J_AsioDataBase &asioData);
	virtual const char *GetResourceType(); 
	virtual int Convert(const j_char_t *pInputData, J_StreamHeader &streamHeader, j_char_t *pOutputData, int &nOutLen);
	virtual int Complete(J_AsioDataBase &asioData);

private:
	bool GetPS(const char *pData, int nLen);
	bool GetConfig(const char *pData, int nLen);
	int ParserUri(const char *request);
	int ParserHeaders(const char *request);
private:
	J_MuxFilter *m_muxFilter;
	J_MediaContext *m_mediaContext;

	int m_nCseq;
	int m_nRtspMethord;

	char m_sps[32];
	char m_pps[32];
	char m_config[16];
	char m_profile_id[4];
	char m_ssrc[16];
	char m_client_ip[16];

	char m_content_base[128];
	char m_sdp_temp[1024];

	int m_video_port;
	int m_audio_port;
	char m_interleaved[10];
	bool m_bPS_Ready;
	bool m_bConfig_Ready;
	int m_protocolStatus;
	unsigned int m_video_ssrc;
	unsigned int m_audio_ssrc;

	std::string m_strVodParam;
	j_char_t m_read_buff[1024];
	j_int32_t m_read_len;
	j_char_t m_send_buff[1024];
};

#endif //~__RTSP_H_
