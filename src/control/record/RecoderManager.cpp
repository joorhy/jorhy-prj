#include "RecoderManager.h"
#include "RecordMediaObj.h"

CRecoderManager::CRecoderManager(int)
{
    m_bStart = false;
    m_thread = 0;

    Init();
}

CRecoderManager::~CRecoderManager()
{

    Deinit();
}

int CRecoderManager::Init()
{
    m_bStart = true;
    pthread_create(&m_thread, NULL, CRecoderManager::WorkThread, this);

    m_timer.Create(120000, CRecoderManager::TimerThread, this);

	J_OS::LOGINFO("CRecoderManager::StartService");
    return J_OK;
}

int CRecoderManager::Deinit()
{
    if (m_bStart)
	{
		m_bStart = false;
		m_timer.Destroy();
        pthread_cancel(m_thread);
		pthread_join(m_thread, NULL);

        J_OS::LOGINFO("CRecoderManager::StopService");
	}
    return J_OK;
}

int CRecoderManager::AddRecord(const char *pResid)
{
    TLock(m_locker);
    m_recordVec.push_back(pResid);
    TUnlock(m_locker);

    return J_OK;
}

int CRecoderManager::DelRecord(const char *pResid)
{
    TLock(m_locker);
    RecordVec::iterator it = m_recordVec.begin();
    for (; it!=m_recordVec.end(); it++)
    {
        if (*it == pResid)
        {
            m_recordVec.erase(it);
            break;
        }
    }
    TUnlock(m_locker);
    StopRecord(pResid);

    return J_OK;
}

int CRecoderManager::StartRecord(const char *pResid)
{
    int nRet = J_UNKNOW;
    TLock(m_locker2);
	MediaMap::iterator it = m_mediaMap.find(pResid);
	if (it == m_mediaMap.end())
	{
		RecordInfo info;
		info.pRecord = new CStreamRecord();
		info.nCount = 0;
		//m_mediaMap[pResid] = info;
		nRet = info.pRecord->StartRecord(pResid);
        if (nRet == J_OK)
		{
            m_mediaMap[pResid].nCount = 1;
			m_mediaMap[pResid] = info;
		}

	}
	else
	{
		if (it->second.nCount == 0)
			nRet = it->second.pRecord->StartRecord(pResid);

        if (nRet == J_OK)
            ++it->second.nCount;
	}
	TUnlock(m_locker2);

	return nRet;
}

int CRecoderManager::StopRecord(const char *pResid)
{
    int nRet = J_OK;
    TLock(m_locker2);
	MediaMap::iterator it = m_mediaMap.find(pResid);
	if (it == m_mediaMap.end())
	{
		J_OS::LOGINFO("CDeviceControl::StopRecord not exist, resid = %s", pResid);
		TUnlock(m_locker2);
		return J_NOT_EXIST;
	}
	else
	{
		if (it->second.nCount == 1)
		{
			nRet = it->second.pRecord->StopRecord(pResid);
            m_mediaMap.erase(it);

			it->second.nCount = 0;
		}
		else
		{
			--it->second.nCount;
		}
	}
	TUnlock(m_locker2);

	return nRet;
}

void CRecoderManager::OnWork()
{
    MediaMap::iterator it;
    while (m_bStart)
	{
		usleep(10);
	    TLock(m_locker2);
	    if (m_mediaMap.empty())
	    {
	        usleep(1000);
	    }
	    it = m_mediaMap.begin();
        for (;it != m_mediaMap.end(); it++)
        {
            if (it->second.pRecord->OnWriteVideo() != J_OK)
            {
                //断线重连处理
                //J_OS::LOGINFO("Stop Recode");
                if (it->second.nCount == 1)
                {
                    it->second.pRecord->StopRecord(it->first.c_str());
                    it->second.nCount = 0;
                }
                else
                {
                    --it->second.nCount;
                }
                //J_OS::LOGINFO("Stop Recode2");
                TLock(m_locker);
                m_recordVec.push_back(it->first);
                TUnlock(m_locker);
            }
        }
        TUnlock(m_locker2);
	}
}

void CRecoderManager::OnTimer()
{
	TLock(m_locker);
	while (!m_recordVec.empty())
	{
		RecordVec::iterator it = m_recordVec.begin();
		for (; it != m_recordVec.end(); it++)
		{
			if (StartRecord(it->c_str()) == J_OK)
			{
				J_OS::LOGINFO("CRecoderManager::OnTimer %s Recode Sucess", it->c_str());
				m_recordVec.erase(it);
				break;
			}
		}
		if (it == m_recordVec.end())
            break;

		//usleep(1000);
	}
	//J_OS::LOGINFO("CControlManager::OnTimer() %d %d", m_recordVec.size(), m_recordVec.empty());
	TUnlock(m_locker);
}
