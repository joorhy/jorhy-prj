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
	int StartVideo(const char *pResId, int nStreamType, const j_socket_t nSocket);	//启动某一路视频
	int StopVideo(const char *pResId, int nStreamType, const j_socket_t nSocket);		//关闭某一路视频

	int StartVoice(const char *pResId, const j_socket_t nSocket);	//启动一路对讲
	int StopVoice(const char *pResId, const j_socket_t nSocket);		//关闭一路对讲

	int GetParser(const char *pResId, J_StreamParser *&pObj);			//获得视频解析器
	int DelParser(const char *pResId);										//删除视频解析器

	int GetRingBuffer(const char *pResId, int nStreamType, const j_socket_t nSocket, CRingBuffer *&pRingBuffer);		//获取某一路的视频的流队列
	int DelRingBuffer(const char *pResId, int nStreaType, const j_socket_t nSocket);									//销毁一路视频的流队列

	int GetVodStream(j_socket_t nSocket, const char *pResId, J_RemoteVod *&pObj);						//获得DVR录像点播流
	int DelVodStream(j_socket_t nSocket, const char *pResId);												//删除DVR录像点播流

	//查找DVR上的录像文件
	int FindVodFile(const char *pResid, time_t beginTime, time_t endTime, std::vector<J_FileInfo> &fileList);

	int OnAlarm(int nDvrId, int nChannel, int nAlarmType);			//上传报警事件

private:
	typedef std::map<j_socket_t, CRingBuffer *> RingBufferMap;
	struct StreamInfo
	{
		void *videoStream;								//void *代表J_VideoStream对象
		RingBufferMap ringBufferMap;
	};
	typedef std::map<J_ChannelKey, StreamInfo> StreamMap;
	StreamMap m_streamMap;

	std::map<j_string_t, void *> m_parserMap;			//void *代表J_VideoParser对象
	std::map<j_socket_t, void *> m_vodMap;						//void *代表J_VideoVodStream对象
};

extern JO_API CAdapterManager* single_adapter_manager;
extern JO_API CAdapterManager* X_JO_API GetAdapterManagerLayer();  

#endif // ~__AdapterManager_h_
