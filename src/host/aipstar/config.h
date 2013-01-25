/***************************************************************************
                          config.h  -  description
                             -------------------
    begin                : 2/6 2004
    copyright            : (C) 2004 by root
    email                : shi_jin_hua@l263.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#define WINVER				0x0500

#include <windows.h>
#include <Winsock2.h>
#include <WS2TCPIP.H>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <shlwapi.h>
#include <process.h>
#include <sys/stat.h>
#include <mmsystem.h>
#include <fcntl.h>
#include <Iphlpapi.h>
#include <Winioctl.h>

#else

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>	
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/ioctl.h> 
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/wait.h>
#include <netdb.h>
#include <dlfcn.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>

#ifndef __BOOL__
#define __BOOL__
typedef int						BOOL;
#endif

typedef unsigned char			BYTE;

#define VIRTUAL					virtual
#define CALLBACK				
#define WINAPI

//#define TRUE					1
//#define FALSE					0
#define MAX_PATH				PATH_MAX
#define INVALID_SOCKET			-1
#define INVALID_HANDLE_VALUE	0
#define SOCKET_ERROR			-1
#define VIRTUAL					virtual
#define HANDLE					void*
#define HINSTANCE				void*
#define HMODULE					void*
#define HWND					void*
#define PLONG					long*
#define LPVOID					void*
#define LPDWORD					unsigned int*
#define HDC						void*
#define LPCVOID					const void*
#define VOID					void
#define	SOCKET					int
#define WAIT_OBJECT_0			0
#define WSAEVENT				HANDLE
#define HTHREAD					pthread_t
#define THREAD_RET				void*
#define TCHAR					char
#define WAVE_FORMAT_PCM			1

typedef struct tagRECT
{
	int left; 
	int top; 
	int right; 
	int bottom;
}RECT;

#endif //WIN32

#endif	//__CONFIG_H__
