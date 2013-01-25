#ifndef __AdapterManager_h_
#define __AdapterManager_h_
#include "j_includes.h"
#include "AdapterFactory.h"

class CAdapterManager : public SingletonTmpl<CAdapterManager>
{
public:
	CAdapterManager(int);
	~CAdapterManager();

protected:
	CAdapterManager();

public:
	int StartVideo(const char *pResId, int nStreamType, const int nSocket);	//启动某一路视频
	int StopVideo(const char *pResId, int nStreamType, const int nSocket);		//关闭某一路视频

	int StartVoice(const char *pResId, const int nSocket);	//启动一路对讲
	int StopVoice(const char *pResId, const int nSocket);		//关闭一路对讲

	int GetParser(const char *pResId, J_StreamParser *&pObj);			//获得视频解析器
	int DelParser(const char *pResId);										//删除视频解析器

	int GetRingBuffer(const char *pResId, int nStreamType, const int nSocket, CRingBuffer *&pRingBuffer);		//获取某一路的视频的流队列
	int DelRingBuffer(const char *pResId, int nStreaType, const int nSocket);									//销毁一路视频的流队列

	int GetVodStream(int nSocket, const char *pResId, J_RemoteVod *&pObj);						//获得DVR录像点播流
	int DelVodStream(int nSocket, const char *pResId);												//删除DVR录像点播流

	//查找DVR上的录像文件
	int FindVodFile(const char *pResid, time_t beginTime, time_t endTime, std::vector<J_FileInfo> &fileList);

	int OnAlarm(int nDvrId, int nChannel, int nAlarmType);			//上传报警事件

private:
	typedef std::map<int, CRingBuffer *> RingBufferMap;
	struct StreamInfo
	{
		void *videoStream;								//void *代表J_VideoStream对象
		RingBufferMap ringBufferMap;
	};
	typedef std::map<J_ChannelKey, StreamInfo> StreamMap;
	StreamMap m_streamMap;

	std::map<std::string, void *> m_parserMap;			//void *代表J_VideoParser对象
	std::map<int, void *> m_vodMap;						//void *代表J_VideoVodStream对象
};

#endif // ~__AdapterManager_h_
