#ifndef __JO_COMMON_H_
#define __JO_COMMON_H_
#include <map>
#include <list>
#include <string>
#include <vector>
#include <queue>

#ifdef WIN32
#include <windows.h>
#include <process.h>
#include <io.h>
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

#ifdef WIN32
#define j_thread_t					HANDLE
#define j_invalid_thread_val		NULL
#else
#define j_thread_t	 pthread_t
#define j_invalid_thread_val 0
#endif

#ifdef WIN32
#define X_JO_API __stdcall
#else
#define X_JO_API 
#endif

#ifdef WIN32
typedef unsigned (X_JO_API *j_thread_entry_t)(void*);
#else
typedef void *(*j_thread_entry_t)(void *); 
#endif 

#ifdef WIN32
typedef struct
{
	CRITICAL_SECTION mutex;
}j_mutex_t;
#else
typedef struct  
{
	pthread_mutex_t mutex;
}j_mutex_t;
#endif

#ifdef WIN32
typedef struct
{
	HANDLE  hFile;
	char *flock;
}j_filemap_t;
#define j_invalid_filemap_val		NULL
#else
typedef struct  
{
	int hFile;
	struct flock flock;
}j_filemap_t;
#define j_invalid_filemap_val		-1
#endif

#ifdef WIN32
typedef struct
{
	HANDLE   handle;
}j_cond_t;
#else
typedef struct
{
	pthread_cond_t   handle;
	pthread_mutex_t mutex;
}j_cond_t;
#define ULONG_MAX 0xffffffffUL
#endif

#endif //~__JO_COMMON_H_
