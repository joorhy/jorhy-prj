#ifndef __J_VIDEOADAPTER_H_
#define __J_VIDEOADAPTER_H_

#include "j_obj.h"
#include "j_type.h"
#include "x_ringbuffer.h"
#include "x_log.h"
#include "x_errtype.h"
#include "x_lock.h"

///任务
class J_Task : virtual public J_Obj
{
	public:
		void *m_pParam;

		///任务的工作函数,由使用者实现
		///@return 参见x_error_type.h
		virtual int Run() = 0;
};
typedef std::queue<J_Task *> j_queue_task;

struct J_DevAdapter : virtual public J_Obj
{
	///获得设备状态
	///@return 		READY-已经登录, BROKEN-断线或者未登录状态
	virtual J_DevStatus GetStatus() const  = 0;

	///断线通知
	///@return 		参见x_error_type.h
	virtual int Broken() = 0;

	///构造视频通道对象
	///@param[in] 	pResid 全局唯一标识
	///@param[out] pObj 构造对象的返回值
	///@param[in]	pOwner channel对象所属的adapter
	///@param[in]	nChannel 通道号
	///@param[in] 	nStream 码流类型, 0-主码流, 1-子码流
	///@param[in] 	nMode 传输方式 0-TCP, 1-UDP
	///@return 		参见x_error_type.h
	virtual int MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream = 0, int nMode = 0) = 0;
};

struct J_DevInput : virtual public J_Obj
{
	///报警布防
	///@return 		参见x_error_type.h
	virtual int EnableAlarm() = 0;

	///报警撤防
	///@return 		参见x_error_type.h
	virtual int DisableAlarm() = 0;

	///报警事件上传
	///param[in]	nDvrId 报警设备ID
	///param[in]	nChannel 报警通道号
	///param[in]	nAlarmype 报警类型
	///@return 		参见x_error_type.h
	virtual int EventAlarm(int nDvrId, int nChannel, int nAlarmType) = 0;
};

struct J_VoiceIcom : virtual public J_Obj
{
	///构造对讲通道对象
	///@param[in] 	pResid 全局唯一标识
	///@param[out] pObj 构造对象的返回值
	///@param[in]	pOwner channel对象所属的adapter
	///@param[in]	nChannel 通道号
	///@return 		参见x_error_type.h
	virtual int MakeVoice(const char *pResid, void *&pObj, void *pOwner, int nChannel) = 0;
};

struct J_ChannelStream : virtual public J_Obj
{
	///打开视频流
	///@param[out] 	pObj 构造对象的返回值
	///@param[in]	pRingBuffer 环形流队列对象,由StreamManager管理
	///@return 		参见x_error_type.h
	virtual int OpenStream(void *&pObj, CRingBuffer *pRingBuffer) = 0;

	///关闭视频流
	///@param[in] 	pObj 将要关闭的流对象
	///@param[in] 	pRingBuffer 环形流队列对象,由StreamManager管理
	///@return 		参见x_error_type.h
	virtual int CloseStream(void *pObj, CRingBuffer *pRingBuffer) = 0;

	///是否支持码流类型
	///@return 		true-支持,false-不支持
	virtual bool HasMultiStream() = 0;
};

struct J_PtzControl : virtual public J_Obj
{
	///云台控制
	///@param[in]	nCmd 云台控制命令, 见NvrType.h
	///@param[in]	nParam 云台控制参数,
	///				nParam > 0,如果云台控制命令为PTZ_PRE_SET or PTZ_PRE_CLR or PTZ_GOTO_PRE,参数为预置点位置;其他命令,参数为速度,取值范围1-255;
	///				nParam = 0,表示停止命令
	///@return		见x_error_type.h
	virtual int PtzControl(int nCmd, int nParam) = 0;
};

struct J_RemoteVod : virtual public J_Obj
{
	///枚举录像文件列表
	///@param[in]	beginTime 查询的起始时间
	///@param[in]	endTime	查询的结束时间
	///@param[out]	fileList 查询结果
	///@return 		参见x_error_type.h
	virtual int EmunFileByTime(time_t beginTime, time_t endTime, std::vector<J_FileInfo> &fileList) = 0;

	///打开DVR录像点播流
	///@param[out] 	pObj 构造对象的返回值
	///@return 		参见x_error_type.h
	virtual int OpenVodStream(void *&pObj) = 0;

	///关闭DVR录像点播流
	///@param[in] 	pObj 将要关闭的解析器对象
	///@return 		参见x_error_type.h
	virtual int CloseVodStream(void *pObj) = 0;
};

struct J_StreamParser : virtual public J_Obj
{
	///打开视频流分析器
	///@param[out] 	pObj 构造对象的返回值
	///@return 		参见x_error_type.h
	virtual int OpenParser(void *&pObj) = 0;

	///关闭视频流分析器
	///@param[in] 	pObj 将要关闭的解析器对象
	///@return 		参见x_error_type.h
	virtual int CloseParser(void *pObj) = 0;
};

struct J_MediaStream : virtual public J_Obj
{
	///启动流传输
	///@return 		参见x_error_type.h
	virtual int Startup() = 0;

	///停止流传输
	///@return 		参见x_error_type.h
	virtual int Shutdown() = 0;

	///添加目标流
	///@param[in] 	pRingBuffer 环形流队列对象,由J_VideoStream管理
	///@return 		参见x_error_type.h
	virtual int AddRingBuffer(CRingBuffer *pRingBuffer) = 0;

	///删除目标流
	///@param[in] 	pRingBuffer 环形流队列对象,由J_VideoStream管理
	///@return 		参见x_error_type.h
	virtual int DelRingBuffer(CRingBuffer *pRingBuffer) = 0;

	///流对象中流队列的数目
	///@return 		流队列个数
	virtual int RingBufferCount() = 0;
};

/*struct J_MediaRecord : virtual public J_Obj
{
	///启动视频录像
	///@param[in] 	pResid 全局唯一标识
	///@param[in] 	nDuration 录像持续时间,单位毫秒
	///@return 		参见x_error_type.h
	virtual int StartRecord(const char *pResid, int nDuration) = 0;

	///停止视频录像
	///@param[in] 	pResid 全局唯一标识
	///@return 		参见x_error_type.h
	virtual int StopRecord(const char *pResid) = 0;
};*/

struct J_MediaParser : virtual public J_Obj
{
	///初始化解析器
	///@param		nDataType 数据类型
	///@return 		参见x_error_type.h
	virtual int Init(int nDataType) = 0;

	///逆初始化解析器
	virtual int Deinit() = 0;

	///输入音视频数据
	///@param[in] 	pData 音视频数据
	///@param[in] 	nLen 数据长度
	///@return 		参见x_error_type.h
	virtual int InputData(const char *pData, int nLen) = 0;

	///获取一包数据
	///@param[out] 	pData 音视频数据
	///@param[out]		streamHeader 流数据头信息
	///@return 			参见x_error_type.h
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader) = 0;
};

struct J_MediaObj : virtual public J_Obj
{
	///处理事务
	///@param[in]	nIoType 事务类型,见NvrType.h
	///@param[in]	nCmdType 命令类型
	///@return 		参见x_error_type.h
	virtual int Process(int nIoType) = 0;

	///清除Client资源
	///@return 		参见x_error_type.h
	virtual int Clearn() = 0;

	///运行
	///@return 		参见x_error_type.h
	virtual int Run(bool bFlag = true) = 0;
};

struct J_RealMediaObj : virtual public J_Obj
{
	///获取Client的资源ID
	///@return 		资源ID,错误返回NULL
	virtual const char *GetResid() const = 0;
};

struct J_RemoteVodStream : virtual public J_Obj
{
	///开始播放
	virtual int Play(time_t beginTime, time_t endTime, CRingBuffer *&pRingBuffer) = 0;

	///停止播放
	virtual int Stop() = 0;

	///暂停播放
	virtual int Pause() = 0;

	///设置播放速度
	virtual int SetSpeed(int nSpeed, bool bFlag = true) = 0;

	///设置播放位置
	virtual int SetPos() = 0;
};

struct J_FileReader : virtual public J_Obj
{
	///获得媒体上下文信息
	///@param[out]	MediaContext 上下文描述信息,需要调用者释放资源
	///@return 		参见x_error_type.h
	virtual int GetContext(J_MediaContext *&mediaContext) = 0;

	///获得媒体数据包
	///@return 		参见x_error_type.h
	virtual int GetPacket(char *pBuffer, J_StreamHeader &streamHeader) = 0;

	///暂停
	///@return 		参见x_error_type.h
	virtual int Pause() = 0;

	///设置速度
	///@param[in]	nScale速度比例
	///@return 		参见x_error_type.h
	virtual int SetScale(float nScale = 1) = 0;

	///设置时间
	///@param[in]	s_time绝对开始时间或者相对开始时间
	///@param[in]	e_time绝对结束时间或者相对结束时间
	///@return 		参见x_error_type.h
	virtual int SetTime(j_uint64_t s_time, j_uint64_t e_time) = 0;

	///设置位置
	///@param[in]	nPos相对开始位置的偏移
	///@return 		参见x_error_type.h
	virtual int SetPosition(int nPos) = 0;
	
	///获取视频数据
	///@param[in]	beginTime开始时间
	///@param[in]	nIval时间间隔
	///@return 		参见x_error_type.h
	virtual int GetMediaData(j_uint64_t beginTime, int nIval) = 0;
};

struct J_JoManager : virtual public J_Obj
{
	///获取设备信息
	///@param[in]	pResid 资源标示
	///@param[out]	devInfo 设备信息
	///@return 		参见x_error_type.h
	virtual int GetDeviceInfo(const char *pResid, J_DeviceInfo &devInfo) = 0;
	
	///列举所有设备
	///@param[out]	devList 全部设备信息
	///@return 		参见x_error_type.h
	virtual int ListDevices(std::vector<J_DeviceInfo> &devList) = 0;

	///通过通道查询通道信息
	///@param[in]	channelId 通道标示
	///@param[out]	channelInfo 通道信息
	///@return 		参见x_error_type.h
	virtual int GetChannelInfo(const char *channelId, J_ChannelInfo &channelInfo) = 0;

	///得到录像相关信息
	///@param[out]	recordInfo 录像相关信息
	///@return 		参见x_error_type.h
	virtual int GetRecordInfo(J_RecordInfo &recordInfo) = 0;
	
	///启动录像
	///@return 		参见x_error_type.h
	virtual int StartRecord() = 0;
	
	///停止录像
	///@return 		参见x_error_type.h
	virtual int StopRecord() = 0;
};

struct J_CommandFilter : virtual public J_Obj
{
	///获取命令类型
	///@return 	命令类型,见j_nvrtype.h
	virtual int GetCommandType() const { return m_nCommandType; }

	///获取资源ID
	///@return 	资源ID
	virtual const char *GetResid() const { return m_strResid; }

	///获取码流类型
	///@return 	码流类型
	virtual int GetStreamType() const { return m_nStreamType; }

protected:
	int m_nCommandType;
	int m_nStreamType;
	char m_strResid[16];
};

struct J_VodCommandFilter : public J_CommandFilter
{
	///获得开始时间
	///@return		开始时间
	virtual j_uint64_t GetBeginTime() const { return m_beginTime; }

	///获得结束时间
	///@return		结束时间
	virtual j_uint64_t GetEndTime() const { return m_endTime; }

	///获得播放速度
	///@return 		播放速度
	virtual j_int32_t GetScale() const { return m_scale; }
	
	///获得播放模式
	///@return 		播放模式
	virtual j_int32_t GetMode() const { return m_mode; }

protected:
	j_uint64_t m_beginTime;
	j_uint64_t m_endTime;
	j_int32_t m_scale;
	j_int32_t m_mode;
};

struct J_RequestFilter : virtual public J_Obj
{
	///命令解析
	///@param[in]	nSocket	
	///@return		见x_error_type.h
	virtual j_result_t Parser(j_socket_t nSocket) = 0;
	
	///获取资源类型
	///@return	成功-资源类型,失败-NULL
	virtual const j_char_t *GetResourceType() = 0;

	///数据转换
	///@param[in]	pInputData 		输入数据
	///@param[in]	streamHeader 	输入数据长度
	///@param[out] 	pOutputData		输出数据
	///@param[out]	nOutputLen		输出数据长度
	///@return		见x_error_type.h
	virtual j_result_t Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen) = 0;

	///完成会话
	///@param[in]	nSocket	
	///@return		见x_error_type.h
	virtual j_result_t Complete(j_socket_t nSocket) = 0;
};

struct J_MuxFilter : virtual public J_Obj
{
	///初始化
	///@return	见x_error_type.h
	virtual j_result_t Init() = 0;

	///逆初始化
	virtual j_void_t Deinit() = 0;

	///数据转换
	///@param[in]	pInputData 		输入数据
	///@param[in]	streamHeader 	输入数据长度
	///@param[out] 	pOutputData		输出数据
	///@param[out]	nOutputLen		输出数据长度
	///@param[in]	pExtdata			扩展数据
	///@return		见x_error_type.h
	virtual j_result_t Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata = 0) = 0;
};

struct J_AsioUser : public J_Obj
{
	///连接事件触发(用于网络IO)
	///@param[in]	nfd IO设备描述符
	///@return		见x_error_type.h
	virtual j_result_t OnAccept(int nfd) = 0;

	///读事件触发
	///@param[in]	nfd IO设备描述符
	///@return		见x_error_type.h
	virtual j_result_t OnRead(int nfd) = 0;

	///写事件触发
	///@param[in]	nfd IO设备描述符
	///@return		见x_error_type.h
	virtual j_result_t OnWrite(int nfd) = 0;

	///断线事件触发(用于网络IO)
	///@param[in]	nfd IO设备描述符
	///@return		见x_error_type.h
	virtual j_result_t OnBroken(int nfd) = 0;
};

struct J_CommandParser : public J_Obj
{
	///添加用户
	///@param[in]	nSocket 用户ID
	///@param[in]	pAddr 用户Address
	///@param[in]	nPort 用户Port
	///@return		见x_error_type.h
	virtual j_result_t AddUser(j_socket_t nSocket, const char *pAddr, short nPort) = 0;
	
	///解析命令
	///@param[in]	nSocket 用户ID
	///@param[in]	pResponse 返回数据
	///@param[out]	nRespLen 返回数据长度
	///@return		见x_error_type.h
	virtual j_result_t ProcessRequest(j_socket_t nSocket, char *&pResponse, int &nRespLen) = 0;
	
	///删除用户
	///@param[in]	nSocket 用户ID
	///@return		见x_error_type.h
	virtual j_result_t DelUser(j_socket_t nSocket) = 0;
};

struct J_EventParser : public J_Obj
{
	///事件解析
	///@param[in]	pEventData 事件数据
	///@return		见x_error_type.h
	virtual j_result_t AnalyzePacket(const unsigned char *pEventData) = 0;
};

template <typename CBase>
class J_BaseVideoStream : public CBase
{
protected:
	J_BaseVideoStream() {}
	~J_BaseVideoStream() {}

public:
	int AddRingBuffer(CRingBuffer *pRingBuffer)
	{
		TLock(m_vecLocker);
		m_vecRingBuffer.push_back(pRingBuffer);
		TUnlock(m_vecLocker);

		return J_OK;
	}

	int DelRingBuffer(CRingBuffer *pRingBuffer)
	{
		TLock(m_vecLocker);
		std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
		for (; it != m_vecRingBuffer.end(); it++)
		{
			if (*it == pRingBuffer)
			{
				m_vecRingBuffer.erase(it);
				TUnlock(m_vecLocker);

				return J_OK;
			}
		}
		TUnlock(m_vecLocker);
		return J_NOT_EXIST;
	}

	int RingBufferCount()
	{
		TLock(m_vecLocker);
		int count = m_vecRingBuffer.size();
		TUnlock(m_vecLocker);

		return  count;
	}

public:
	J_OS::TLocker_t m_vecLocker;
	std::vector<CRingBuffer *> m_vecRingBuffer;
};

///全局标识
template <template <typename CBase> class CBaseAdapter, typename CChannel = J_ChannelStream>
class J_ResidTmpl : public CBaseAdapter<CChannel>
{
public:
	std::string m_resid;
};

#endif //~__J_VIDEOADAPTER_H_
