#ifndef __X_BUFFER_H_
#define __X_BUFFER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/thread.h>

#define BUFFER_SIZE (1024 * 1024 * 50)

struct J_MEMNODE
{
	int nLen;
	char *pData;
};
#define J_MEMNODE_LEN (sizeof(J_MEMNODE))

class CXBuffer
{
	public:
		CXBuffer(int nBuffSize = BUFFER_SIZE);
		~CXBuffer();
	
	public:
		int PushData(const char *pData, int nLen);
		int PopData(char *pData);
	
	private:
		void Read(char *pData, int nLen);
		void Write(const char *pData, int nLen);
		int GetIdleLength();
		void EraseBuffer();
		char *AddBuffer(char *pBuffer, int nLen);
		
	private:
		wxMutex m_locker;
		char *m_pBuffer;
		char *m_pBegin;
		char *m_pEnd;
		
		char *m_pWritePoint;
		char *m_pReadPoint;
		int m_nDataLen;
		
		J_MEMNODE m_Node;
};

#endif //~__X_BUFFER_H_