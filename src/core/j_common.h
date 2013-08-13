#ifndef __JO_COMMON_H_
#define __JO_COMMON_H_

#include "j_obj.h"
#define JO_DECLARE_SINGLETON(_name) \
	extern JO_API C##_name* Single_##_name; \
	extern JO_API C##_name* X_JO_API Get##_name##Layer();  

#define  JO_IMPLEMENT_SINGLETON(_name) \
	C##_name* Single_##_name = NULL; \
	C##_name* X_JO_API Get##_name##Layer() \
	{\
		if (Single_##_name == NULL) \
			Single_##_name = new C##_name(); \
		return Single_##_name; \
	}

#define JO_INSTANSE(_name) \
	Get##_name##Layer()

///资源管理Singleton对象
#define JoResourceManager \
	JO_INSTANSE(ResourceManager)
///设备工厂Singleton对象
#define JoAdapterFactory \
	JO_INSTANSE(AdapterFactory)
///设备管理Singleton对象
#define JoAdapterManager \
	JO_INSTANSE(AdapterManager)
///解码器工厂Singleton对象
#define JoDecoderFactory \
	JO_INSTANSE(DecoderFactory)
///视频显示器工厂Singleton对象
#define JoRenderFactory \
	JO_INSTANSE(RenderFactory)
///文件分析器工厂Singleton对象
#define JoFileReaderFactory \
	JO_INSTANSE(FileReaderFactory)
///协议过滤器工厂Singleton对象
#define JoFilterFactory \
	JO_INSTANSE(FilterFactory)
///私有协议SDK Singleton对象
#define JoXJoSdk \
	JO_INSTANSE(XJoSdk)
///管理设备工厂Singleton对象
#define JoManagerFactory \
	JO_INSTANSE(ManagerFactory)
///流合成器工厂Singleton对象
#define JoMuxFactory \
	JO_INSTANSE(MuxFactory)
///协议分析器工厂Singleton对象
#define JoParserFactory \
	JO_INSTANSE(ParserFactory)
///播放器工厂Singleton对象
#define JoPlayerFactory \
	JO_INSTANSE(PlayerFactory)
///MC协议SDK Singleton对象
#define JoXSdk \
	JO_INSTANSE(XSdk)
///异步IO  Singleton对象
#define JoXAsio \
	JO_INSTANSE(XAsio)
///线程池 Singleton对象
#define JoThreadPool \
	JO_INSTANSE(ThreadPool)
///时间 Singleton对象
#define JoTime \
	JO_INSTANSE(Time)
///录像管理器 Singleton对象
#define JoRecoderManager \
	JO_INSTANSE(RecoderManager)
///播放管理器Singleton对象
#define JoPlayManager \
	JO_INSTANSE(PlayManager)
///录像文件管理器Singleton对象
#define JoVodManager \
	JO_INSTANSE(XVodManager)
///报警管理Singleton对象
#define JoAlarmManager \
	JO_INSTANSE(AlarmManager)

#include "x_errtype.h"

typedef bool 								j_boolean_t;
typedef unsigned int						j_time_t;
typedef char									j_char_t;
typedef int									j_result_t;
typedef long									j_long_t;
typedef void									j_void_t;

typedef char 								j_int8_t;
typedef unsigned char					j_uint8_t;
typedef short 								j_int16_t;
typedef unsigned short 				j_uint16_t;
typedef int 									j_int32_t;
typedef unsigned int 					j_uint32_t;
typedef long long 						j_int64_t;
typedef unsigned long long 			j_uint64_t;
typedef float									j_float_t;

typedef std::string							j_string_t;	
typedef std::vector<j_string_t>		j_vec_str_t;

typedef unsigned char					j_uuid_t[16];

#ifdef WIN32
#define j_thread_t						HANDLE
#define j_invalid_thread_val		NULL
#define j_invalid_filemap_val		NULL
#define j_invalid_module_val		NULL
#define j_invalid_socket_val		INVALID_SOCKET
#else
#define ULONG_MAX				0xffffffffUL
#define j_thread_t	 pthread_t
#define j_invalid_thread_val		0
#define j_invalid_filemap_val		-1
#define j_invalid_module_val		NULL
#define j_invalid_socket_val		-1
#endif

#ifdef WIN32
#define j_sleep(x)	Sleep(x)
#define j_close_socket(x)	closesocket(x)
#else
#define j_sleep(x)	usleep(x*1000)
#define j_close_socket(x)	close(x)
#endif

#ifdef WIN32
#define j_atoll(x) _atoi64(x)
#else
#define j_atoll(x) atoll(x)
#endif

#ifdef WIN32
typedef unsigned (X_JO_API *j_thread_entry_t)(void*);
#else
typedef void *(*j_thread_entry_t)(void *); 
#endif 


typedef struct
{
#ifdef WIN32
	CRITICAL_SECTION mutex;
#else
	pthread_mutex_t mutex;
#endif
}j_mutex_t;

typedef struct
{
#ifdef WIN32
	HANDLE  hFile;
	char *flock;
#else
	int hFile;
	struct flock flock;
#endif
}j_filemap_t;

typedef struct
{
#ifdef WIN32
	HANDLE   handle;
#else
	pthread_cond_t   handle;
	pthread_mutex_t mutex;
#endif
}j_cond_t;

typedef struct  
{
#ifdef WIN32
	HMODULE handle;
#else
	void *handle;
#endif
} j_module_t; 

#ifdef WIN32
typedef SOCKET j_asio_handle;
#else
typedef int j_asio_handle;
#endif

typedef struct j_socket
{
	j_socket()
	{
		sock = j_invalid_socket_val;
	}
	j_socket(j_asio_handle s)
	{
		sock = s;
	}
	j_asio_handle sock;
	j_boolean_t operator < (const j_socket &other) const
	{
		return (sock < other.sock);
	}
} j_socket_t;
#define j_invalid_socket j_socket_t

typedef struct 
{
#ifdef WIN32
	DWORD id;
#else
	pid_t id;
#endif
}j_pid_t;

struct J_AsioDataBase
#ifdef WIN32
: public OVERLAPPED
#endif
{
	/// 执行的异步IO调用
	enum J_IoCall
	{
		j_accept_e = 1,
		j_connect_e,
		j_disconnect_e,
		j_read_e,
		j_recvfrom_e,
		j_write_e,
		j_sendto_e,
		j_ioctrl_e
	};

	struct J_IoAccept
	{
		j_asio_handle subHandle;		///< Accept调用完成后得到的handle
		j_uint32_t peerIP;				///< 对端IP地址
		j_int32_t peerPort;				///< 对端端口
	};

	struct J_IoRead
	{
		j_char_t *buf;				///< 接收数据缓冲区
		j_int32_t bufLen;			///< 接收数据缓冲区字节数
		j_boolean_t whole;			///< TRUE-等到全部数据接收完才算成功, FALSE-接收到数据立即成功
		j_boolean_t shared;		///< 
		j_char_t until_buf[16];

		j_boolean_t peerClosed;		///< TRUE-对端已经关闭, FALSE-没有
		j_int32_t finishedLen;		///< 已经接收的数据字节数
	};

	struct J_IoReceiveFrom
	{
		j_char_t *buf;				///< 接收数据缓冲区
		j_int32_t bufLen;			///< 接收数据缓冲区字节数

		j_int32_t finishedLen;		///< 已经接收的数据字节数
		sockaddr_in sender;			///< 发送者的服务器IP地址和端口
	};

	struct J_IoConnect
	{
		struct sockaddr_in server;	///< 要连接的服务器IP地址和端口
	};

	struct J_IoWrite
	{
		j_boolean_t whole;		///< TRUE-等到全部数据发送完才算成功, FALSE-发送部分数据立即成功
		j_boolean_t shared;		///< 
		const j_char_t *buf;	///< 发送数据缓冲区
		j_int32_t bufLen; 		///< 发送数据缓冲区字节数

		j_int32_t finishedLen; 	///< 已经发送的数据字节数
	};

	struct J_IoSendTo
	{
		struct sockaddr_in receiver;	///< 接收者的服务器IP地址和端口
		const j_char_t *buf;			///< 发送数据缓冲区
		j_int32_t bufLen;				///< 发送数据缓冲区字节数

		j_int32_t finishedLen;			///< 已经发送的数据字节数
	};

	struct J_IoIoctl
	{
		j_int32_t cmd;				///< Ioctl命令码
#if defined(WIN32)
		const j_char_t *req;		///< 请求缓冲区
		j_uint32_t reqLen;			///< 请求缓冲区字节数
		j_char_t *reply;			///< 应答缓冲区
		j_uint32_t replyLen; 		///< 应答缓冲区字节数

		j_uint32_t finishedLen; 	///< 实际应答的字节数
#elif defined(__linux__)
		j_int16_t pollEvents; 		///< Ioctl需要poll什么事件(POLLIN/POLLOUT/POLLPRI之一)
		j_void_t *ioctlParm;  		///< Ioctl的参数
#endif
	};

	enum { MAX_CALL_DATA=64, MAX_AGENT_DATA=128 };

	/// Io完成 超时或失败后调用
	/// 必须尽快返回不得阻塞,否则可能影响其他使用者造成性能问题.
	/// @param[in] ioData 异步Io信息块
	/// @param[in] ret 0-失败, <0-见j_errtype.h), 1-超时, >1-保留不得使用
	typedef void (*JoFIoCallback)(J_AsioDataBase& ioData, j_result_t ret);

	j_asio_handle ioHandle;		///异步Io句柄
	J_Obj *ioUser;				///< 异步Io使用者
	J_IoCall ioCall;			/// 执行的异步Io调用
	union
	{
		J_IoAccept ioAccept;
		J_IoRead ioRead;
		J_IoReceiveFrom ioReceiveFrom;
		J_IoConnect ioConnect;
		J_IoWrite ioWrite;
		J_IoSendTo ioSendTo;
		J_IoIoctl ioIoctl;
		j_char_t ioCallData[MAX_CALL_DATA];
	};
};

#ifdef WIN32
typedef HWND j_wnd_t;
#define j_invalid_wnd NULL
#else
typedef Drawable j_wnd_t;
#define j_invalid_wnd 0
#endif

#endif //~__JO_COMMON_H_
