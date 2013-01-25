#ifndef __X_BUFFER_H_
#define __X_BUFFER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/thread.h>

#define BUFFER_SIZE (1024 * 1024 * 10)

struct J_MEMHEAD
{
	int nLen;
	char *pData;
	J_MEMHEAD *pPrev;
	J_MEMHEAD *pNext;
};
#define J_MEMHEAD_LEN (sizeof(J_MEMHEAD))

class CXBuffer
{
	public:
		CXBuffer(int nBuffSize = BUFFER_SIZE);
		~CXBuffer();
	
	public:
		char *LockBuffer(int nLen, bool bFlag = true);
		void UnlockBuffer(bool bFlag = true);
	
	private:
		void AddBusyMem(J_MEMHEAD *pMemHead);
		void AddIdleMem(J_MEMHEAD *pMemHead);
		
	private:
		wxCriticalSection m_criticalSection;
		char *m_pBuffer;
		char *m_pBegin;
		char *m_pEnd;
		
		J_MEMHEAD *m_pBusyMem;
		J_MEMHEAD *m_pIdleMem;
};

#endif //~__X_BUFFER_H_