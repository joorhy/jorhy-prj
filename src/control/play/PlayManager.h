#ifndef __PLAYMANAGER_H_
#define __PLAYMANAGER_H_
#include "j_includes.h"
#include "x_loadso.h"
#include "x_thread.h"

struct J_PlayManagerInfo
{
	j_char_t *host_type;
	j_char_t *host_addr;
	j_int16_t host_port;
	j_uint32_t stream_type;
	j_char_t *resid;
	j_char_t *user_name;
	j_char_t *pass_word;
	j_char_t *player_type;
	j_uint32_t dev_id;
	j_wnd_t play_wnd;
	j_int32_t width;
	j_int32_t height;
	j_uint64_t start_time;
	j_uint64_t end_time;
};

struct J_PlayStreamInfo
{
	J_PlayerObj *pPlayObj;
	j_int32_t nDevid;
	j_boolean_t bStart;
};

class JO_API CPlayManager
{
	typedef std::map<j_int32_t, j_int32_t> AdapterMap;
	typedef std::map<j_int32_t, J_PlayStreamInfo> StreamMap;
public:
	CPlayManager();
	~CPlayManager();

public:
	///³õÊ¼»¯¹ÜÀíÄ£¿é
	///@return	²Î¼ûj_errtype.h
	j_result_t Init();
	///Äæ³õÊ¼»¯¹ÜÀíÄ£¿é
	///@return	void
	void Deinit();
	///´ò¿ªÊÓÆµÁ÷
	///@param	 pUrl-Ô´URL(joh://192.168.1.109:8002?resid=102&username=admin&passwd=admin&stream_type=0)
	///@param	 pUrl-Ä¿µÄURL(jo_player://12345678?width=704&height=576)
	///@return	 Á÷±àºÅ,ºóÐø²Ù×÷¶¼»ùÓÚÕâ¸ö±àºÅ, < 0±íÊ¾Ê§°Ü
	j_int32_t OpenStream(const j_char_t *pUrl, const j_char_t *pUrl2);
	///¹Ø±ÕÊÓÆµÁ÷
	///@param	 streamHandle OpenStreamµÄ·µ»ØÖµ
	///@return	 void
	void CloseStream(j_int32_t streamHandle);
	///´ò¿ªµã²¥Á÷
	///@param	 pUrl-Ô´URL(joh://192.168.1.109:8002?resid=102&username=admin&passwd=admin&start=0&end=0)
	///@param	 pUrl-Ä¿µÄURL(jo_player://12345678)
	///@return	 Á÷±àºÅ,ºóÐø²Ù×÷¶¼»ùÓÚÕâ¸ö±àºÅ, < 0±íÊ¾Ê§°Ü
	j_int32_t OpenVod(const j_char_t *pUrl, const j_char_t *pUrl2);
	///¹Ø±Õµã²¥Á÷
	///@param	 streamHandle OpenVodµÄ·µ»ØÖµ
	///@return	 void
	void CloseVod(j_int32_t streamHandle);

private:
	void InitPlayManagerInfo(J_PlayManagerInfo &info);
	void FreePlayManagerInfo(J_PlayManagerInfo &info);
	j_boolean_t ParserUrl(const j_char_t *pUrl, const j_char_t *pUrl2, J_PlayManagerInfo &info);
	j_boolean_t ParserUrl2(const j_char_t *pUrl, const j_char_t *pUrl2, J_PlayManagerInfo &info);

#ifdef WIN32
	static unsigned X_JO_API WorkThread(void *param)
#else
	static void *WorkThread(void *param)
#endif
	{
		(static_cast<CPlayManager *>(param))->OnWork();
		return 0;
	}
	void OnWork();

private:
	j_boolean_t m_bStart;
	j_int32_t m_nDevId;
	j_int32_t m_nStreamId;
	//CXLoadso m_loadSo;
	AdapterMap m_adapterMap;
	StreamMap m_streamMap;
	CJoThread m_thread;
	J_OS::CTLock m_streamLocker;
	J_OS::CTLock m_adapterLocker;
};

JO_DECLARE_SINGLETON(PlayManager)

#endif //~__PLAYMANAGER_H_