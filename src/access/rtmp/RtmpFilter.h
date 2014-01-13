#ifndef __RTMP_FILTER_H_
#define __RTMP_FILTER_H_

#include "j_includes.h"
#include "x_module_manager_def.h"

enum rtmp_state
{
	rtmp_init = 1,
	rtmp_hand_shake,
	rtmp_hand_shake2,
	rtmp_hand_shake3,
	rtmp_head_type,
	rtmp_head_body,
	rtmp_body,
	rtmp_server_bw,
	rtmp_client_bw,
	rtmp_connect_invoke,
	rtmp_bwdonw_invoke,
	rtmp_create_stream_invoke,
	rtmp_chunk_size,
	rtmp_onstatus_reset_invoke,
	rtmp_onstatus_start_invoke,
	rtmp_access_notify,
	rtmp_start_notify,
	rtmp_metadata_notify,
	rtmp_send_data,
};

enum rmf_data_type
{
	rmf_double = 0,
	rmf_boolean,
	rmf_string,
	rmf_object,
	rmf_null = 5,
	rmf_undefined,
};

class CRtmpFilter : public J_RequestFilter
	, public J_VodCommandFilter
{
public:
	CRtmpFilter();
	~CRtmpFilter();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CRtmpFilter();
		return J_OK;
	}

public:
	///J_ProtocolFilter
	virtual j_result_t Parser(J_AsioDataBase &asioData);
	const j_char_t *GetResourceType();
	virtual j_result_t Convert(const j_char_t *pInputData, J_StreamHeader &streamHeader, j_char_t *pOutputData, j_int32_t &nOutLen);
	virtual j_result_t Complete(J_AsioDataBase &asioData);

private:
	int GetDouble(const char *pData);
	int GetBoolean(const char *pData);
	int GetString(const char *pData, char *pVal = NULL);
	int GetEmpty(const char *pData);
	int GetObjKey(const char *pData);
	int GetObjVal(const char *pData);
	int GetObject(const char *pData);
	int GetHeadLength(const char *pData);
	int ParserMSF(const char *pData);
	int MakeServerBw(char *pData);
	int MakeClientBw(char *pData);
	int MakePing(int nType, int nLen, int nStreamId, int nParam2, char *pData);
	int MakeConnectInvoke(char *pData);
	int MakeOnBWDoneInvoke(char *pData);
	int MakeCreateStreamInvoke(char *pData);
	int MakeChunkSize(char *pData);
	int MakePlayResetInvoke(char *pData);
	int MakePlayStartInvoke(char *pData);
	int MakeAccessNotify(char *pData);
	int MakeStartNotify(char *pData);
	int MakeMetadataNotify(char *pData);

private:
	J_MuxFilter *m_muxFilter;
	j_char_t m_read_buff[4096];
	j_int32_t m_read_len;
	j_int32_t m_state;
};

#endif //~__RTMP_FILTER_H_