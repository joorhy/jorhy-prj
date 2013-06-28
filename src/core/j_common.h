#ifndef __JO_COMMON_H_
#define __JO_COMMON_H_

#ifdef WIN32
#include <process.h>
#include <io.h>
#include <Winsock2.h>
#include <Mstcpip.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#else
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>		/* getopt_long() */
#include <semaphore.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <dlfcn.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <setjmp.h>
#include <netinet/tcp.h>
#endif

#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <signal.h>
#include <fcntl.h>		/* low-level i/o */
#include <errno.h>
#include <cstring>
#include <assert.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>

#include <map>
#include <list>
#include <string>
#include <vector>
#include <queue>
#include <stdexcept>

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
#define X_JO_API __stdcall
#else
#define X_JO_API 
#endif

#ifdef WIN32
#ifdef   JO_EXPORTS 
#define   JO_API           __declspec(dllexport) 
#else 
#define   JO_API           __declspec(dllimport) 
#endif 
#else
#define JO_API  
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
	j_void_t *ioUser;				///< 异步Io使用者
	J_IoCall ioCall;			/// 执行的异步Io调用
	j_int32_t ioTimeOut;		///< 超时设定, -1表示无穷大, 单位:毫秒
	JoFIoCallback ioCallback;	///< Io完成 超时或失败调用
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

#endif //~__JO_COMMON_H_
