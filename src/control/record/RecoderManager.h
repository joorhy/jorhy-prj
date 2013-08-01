#ifndef __RECODERMANAGER_H_
#define __RECODERMANAGER_H_

#include "j_includes.h"
#include "x_singleton.h"
#include "x_timer.h"
#include "RecordMediaObj.h"

class JO_API CRecoderManager
{
    public:
        CRecoderManager();
        ~CRecoderManager();
    public:
        ///CRecoderManager
        int AddRecord(const char *pResid);
        int DelRecord(const char *pResid);
		void Single() { m_cond.Single(); } 

    private:
        int Init();
        int Deinit();
        int StartRecord(const char *pResid);
        int StopRecord(const char *pResid);
#ifdef WIN32
		static unsigned X_JO_API WorkThread(void *param)
#else
		static void *WorkThread(void *param)
#endif
		{
			(static_cast<CRecoderManager *>(param))->OnWork();
			return 0;
		}
		void OnWork();

        static void TimerThread(void *pUser)
        {
            CRecoderManager *pThis = static_cast<CRecoderManager *>(pUser);
            if (pThis != NULL)
                pThis->OnTimer();
        }
        void OnTimer();

    private:
    	struct RecordInfo
        {
            CStreamRecord *pRecord;
            int nCount;
        };
        typedef std::map<std::string, RecordInfo> MediaMap;
        MediaMap m_mediaMap;

        bool m_bStart;
        CJoThread m_thread;

        J_OS::CTimer m_timer;
        typedef std::map<j_string_t, j_boolean_t> RecordVec;
        RecordVec m_recordVec;
        J_OS::CTLock m_locker;
        J_OS::CTLock m_locker2;
		J_OS::CXCond m_cond;
};
JO_DECLARE_SINGLETON(RecoderManager)

#endif //~__RECODERMANAGER_H_
