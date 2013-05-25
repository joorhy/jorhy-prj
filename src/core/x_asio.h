#ifndef __X_RD_ASIO_H_
#define __X_RD_ASIO_H_
#include "j_includes.h"
#include "j_type.h"
#include "x_singleton.h"
#include "x_lock.h"
#include "x_socket.h"
#include "x_thread.h"

/// 异步Io使用者.
typedef j_uint32_t JoAsIoUser;

/// 无效的异步Io使用者
const JoAsIoUser JO_INVALID_ASIO_USER = 0xffffffff;

struct J_AsioDataBase
#ifdef WIN32
: public OVERLAPPED
#endif
{
	/// 执行的异步Io调用
	enum J_IoCall
	{
		J_ACCEPT = 1,
		J_CONNECT,
		J_DISCONNECT,
		J_READ,
		J_RECEIVEFROM,
		J_WRITE,
		J_SENDTO,
		J_IOCTL
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
		j_int32_t bufLen;		///< 接收数据缓冲区字节数
		j_boolean_t whole;	///< TRUE-等到全部数据接收完才算成功, FALSE-接收到数据立即成功

		j_boolean_t peerClosed;	///< TRUE-对端已经关闭, FALSE-没有
		j_int32_t finishedLen;			///< 已经接收的数据字节数
	};

	struct J_IoReceiveFrom
	{
		j_char_t *buf;					///< 接收缓冲区
		j_int32_t bufLen;			///< 接收缓冲区字节数

		j_int32_t finishedLen;		 ///< 已经接收的数据字节数
		sockaddr_in sender;		///< 发送者的服务器IP地址和端口
	};

	struct J_IoConnect
	{
		struct sockaddr_in server;	///< 要连接的服务器IP地址和端口
	};

	struct J_IoWrite
	{
		j_boolean_t whole;	///< TRUE-等到全部数据发送完才算成功, FALSE-发送部分数据则立即成功
		const j_char_t *buf;	///< 发送数据缓冲区
		j_int32_t bufLen; ///< 发送数据缓冲区字节数

		j_int32_t finishedLen; ///< 已经发送的数据字节数
	};

	struct J_IoSendTo
	{
		struct sockaddr_in receiver;	///< 接收者的服务器IP地址和端口
		const j_char_t *buf;				///< 发送数据缓冲区
		j_int32_t bufLen;					///< 发送数据缓冲区字节数

		j_int32_t finishedLen;				///< 已经发送的数据字节数
	};

	struct J_IoIoctl
	{
		j_int32_t cmd;			///< Ioctl命令码
#if defined(WIN32)
		const j_char_t *req;	///< 请求缓冲区
		j_uint32_t reqLen;		///< 请求缓冲区字节数
		j_char_t *reply;			///< 应答缓冲区
		j_uint32_t replyLen; ///< 应答缓冲区字节数

		j_uint32_t finishedLen; ///< 实际应答的字节数
#elif defined(__linux__)
		j_int16_t pollEvents; ///< Ioctl需要poll什么事件(POLLIN/POLLOUT/POLLPRI之一)
		j_void_t *ioctlParm;  ///< Ioctl的参数
#endif
	};

	enum { MAX_CALL_DATA=64, MAX_AGENT_DATA=128 };

	/// Io完成、超时或失败后调用.
	/// 必须尽快返回不得阻塞，否则可能影响其它使用者造成性能问题.
	/// @param[in] ioData 异步Io信息块
	/// @param[in] ret 0-完成, <0-失败(见j_errtype.h), 1-超时, >1-保留不得使用
	typedef void (*JoFIoCallback)(J_AsioDataBase& ioData, j_result_t ret);

	JoAsIoUser ioUser;			///< 异步Io使用者
	J_IoCall ioCall;					/// 执行的异步Io调用
	j_int32_t ioTimeOut;			///< 超时设定, -1表示无穷大, 单位:毫秒
	JoFIoCallback ioCallback;	///< Io完成、超时或失败后调用
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

class JO_API CRdAsio : public SingletonTmpl<CRdAsio>
{
public:
	CRdAsio(int);
	~CRdAsio();

private:
	CRdAsio();

public:
	int Init();
	void Deinit();
	int AddUser(j_socket_t nSocket, J_AsioUser *pUser);
	void DelUser(j_socket_t nSocket);

private:
#ifdef WIN32
	static unsigned X_JO_API WorkThread(void *param)
#else
	static void *WorkThread(void *param)
#endif
	{
		(static_cast<CRdAsio *>(param))->OnWork();
		return 0;
	}
	void OnWork();
	void EnableKeepalive(j_socket_t nSocket);

private:
	typedef std::map<j_socket_t, J_AsioUser *> AsioMap;
	AsioMap m_asioMap;

	CJoThread m_workThread;
	J_OS::CTLock m_locker;

	j_boolean_t m_bStarted;
#ifdef WIN32
	fd_set m_fdSet;
	struct timeval m_timeout;
#else
	int m_epoll_fd;
	struct epoll_event m_evAsio;
	struct epoll_event m_evConnect[JO_MAX_ASIOSIZE];
#endif
};

#endif //~__X_RD_ASIO_H_
