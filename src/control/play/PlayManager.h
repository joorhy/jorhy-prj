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
	///初始化管理模块
	///@return	参见j_errtype.h
	j_result_t Init();
	///逆初始化管理模块
	///@return	void
	void Deinit();
	///打开视频流
	///@param	 pUrl-源URL(joh://192.168.1.109:8002?resid=102&username=admin&passwd=admin&stream_type=0)
	///@param	 pUrl-目的URL(jo_player://12345678)
	///@return	 流编号,后续操作都基于这个编号, < 0表示失败
	j_int32_t OpenStream(const j_char_t *pUrl, const j_char_t *pUrl2);
	///关闭视频流
	///@param	 streamHandle OpenStream的返回值
	///@return	 void
	void CloseStream(j_int32_t streamHandle);

private:
	void InitPlayManagerInfo(J_PlayManagerInfo &info);
	void FreePlayManagerInfo(J_PlayManagerInfo &info);
	j_boolean_t ParserUrl(const j_char_t *pUrl, const j_char_t *pUrl2, J_PlayManagerInfo &info);

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
	j_int32_t m_nStreamId;
	j_int32_t m_nDevId;
	//CXLoadso m_loadSo;
	AdapterMap m_adapterMap;
	StreamMap m_streamMap;
	CJoThread m_thread;
	J_OS::CTLock m_streamLocker;
	J_OS::CTLock m_adapterLocker;
};

JO_DECLARE_SINGLETON(PlayManager)

#endif //~__PLAYMANAGER_H_