#include "RecoderManager.h"
#include "RecordMediaObj.h"

CRecoderManager* single_recoder_manager = NULL;
CRecoderManager* X_JO_API GetRecoderManagerLayer()
{
	if (single_recoder_manager == NULL)
		single_recoder_manager = new CRecoderManager();
	return single_recoder_manager;
}

CRecoderManager::CRecoderManager()
{
    m_bStart = false;
    //Init();
}

CRecoderManager::~CRecoderManager()
{
    //Deinit();
}

int CRecoderManager::Init()
{
    m_bStart = true;
	j_thread_parm parm = {0};
	parm.entry = CRecoderManager::WorkThread;
	parm.data = this;
	m_thread.Create(parm);

    m_timer.Create(5000, CRecoderManager::TimerThread, this);

	J_OS::LOGINFO("CRecoderManager::StartService");
    return J_OK;
}

int CRecoderManager::Deinit()
{
    if (m_bStart)
	{
		m_bStart = false;
		m_timer.Destroy();
		m_bStart = false;
		m_thread.Release();

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
		j_sleep(10);
	    TLock(m_locker2);
	    if (m_mediaMap.empty())
	    {
	        j_sleep(1000);
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
					AddRecord(it->first.c_str());//重新开始录像
                }
                else
                {
                    --it->second.nCount;
                }
                //J_OS::LOGINFO("Stop Recode2");
                //TLock(m_locker);
                //m_recordVec.push_back(it->first);
                //TUnlock(m_locker);
            }
        }
        TUnlock(m_locker2);
	}
}

void CRecoderManager::OnTimer()
{
	//m_cond.Wait();
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
	//m_cond.Single();
	//J_OS::LOGINFO("CControlManager::OnTimer() %d %d", m_recordVec.size(), m_recordVec.empty());
	TUnlock(m_locker);
}
