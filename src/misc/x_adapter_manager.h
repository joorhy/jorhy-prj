#ifndef __AdapterManager_h_
#define __AdapterManager_h_
#include "j_includes.h"
#include "x_adapter_factory.h"

class JO_API CAdapterManager
{
public:
	CAdapterManager();
	~CAdapterManager();

public:
	int StartVideo(const char *pResId, int nStreamType, const j_socket_t nSocket, j_int32_t nDevid = -1);	//启动某一路视频
	int StopVideo(const char *pResId, int nStreamType, const j_socket_t nSocket, j_int32_t nDevid = -1);		//关闭某一路视频

	int StartVoice(const char *pResId, const j_socket_t nSocket, j_int32_t nDevid = -1);	//启动一路对讲
	int StopVoice(const char *pResId, const j_socket_t nSocket, j_int32_t nDevid = -1);		//关闭一路对讲

	int GetParser(const char *pResId, J_StreamParser *&pObj, j_int32_t nDevid = -1);			//获得视频解析器
	int DelParser(const char *pResId, j_int32_t nDevid = -1);										//删除视频解析器

	int GetRingBuffer(const char *pResId, int nStreamType, const j_socket_t nSocket, CRingBuffer *&pRingBuffer);		//获取某一路的视频的流队列
	int DelRingBuffer(const char *pResId, int nStreaType, const j_socket_t nSocket);									//销毁一路视频的流队列

	int GetVodStream(j_socket_t nSocket, const char *pResId, J_Obj *&pObj, j_int32_t nDevid = -1);						//获得DVR录像点播流
	int DelVodStream(j_socket_t nSocket, const char *pResId, j_int32_t nDevid = -1);												//删除DVR录像点播流

	//查找DVR上的录像文件
	int FindRemoteFile(const char *pResid, time_t beginTime, time_t endTime, j_vec_file_info_t &vecFileInfo, j_int32_t nDevid = -1);

private:
	typedef std::map<j_socket_t, CRingBuffer *> RingBufferMap;
	struct StreamInfo
	{
		J_Obj *videoStream;								//void *代表J_VideoStream对象
		RingBufferMap ringBufferMap;
	};
	typedef std::map<J_ChannelKey, StreamInfo> StreamMap;
	StreamMap m_streamMap;

	std::map<j_string_t, J_Obj *> m_parserMap;			//void *代表J_VideoParser对象
	std::map<j_socket_t, J_Obj *> m_vodMap;						//void *代表J_VideoVodStream对象
};

JO_DECLARE_SINGLETON(AdapterManager)

#endif // ~__AdapterManager_h_
