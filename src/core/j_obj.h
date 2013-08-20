#ifndef __J_OBJ_H_
#define __J_OBJ_H_

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

struct JO_API J_Obj
{
	virtual ~J_Obj() {}
};

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
#include <X11/Xlib.h>
#include <aio.h>
#include <sys/vfs.h>
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

///原子操作 long型数据
inline long atomic_inc(long volatile *v)
{
#ifdef WIN32
	InterlockedExchangeAdd(v, 1);
#else
	__asm__ __volatile__("lock incl %0" : "+m"(*v));
#endif
	return *v;
}

inline long atomic_dec(long volatile *v)
{
#ifdef WIN32
	InterlockedExchangeAdd(v, -1);
#else
	__asm__ __volatile__("lock decl %0" : "+m"(*v));
#endif
	return *v;
}

///实现引用计数加减
template <typename CBsae>
class J_BaseAdapter : public CBsae
{
protected:
	J_BaseAdapter() : m_nRefCnt(0) {}
	virtual ~J_BaseAdapter() {}

protected:
	long IncRef()
	{
		return atomic_inc(&m_nRefCnt);
	}

	long DecRef()
	{
		return atomic_dec(&m_nRefCnt);
	}

	long GetRef()
	{
		return m_nRefCnt;
	}

protected:
	long m_nRefCnt;
};

#define J_Add_Ref(impl) impl->IncRef();
#define J_Release(impl)\
		if (impl->GetRef() > 1)\
			impl->DecRef();\
		else\
			delete impl;

#endif //~__J_OBJ_H_
