#include "JoissManager.h"
#include "tinyxml.h"

CJoissManager::CJoissManager()
{
    m_sqlite = NULL;
}

CJoissManager::~CJoissManager()
{
	if (m_sqlite != NULL)
	{
		sqlite3_close(m_sqlite);
		m_sqlite = NULL;
	}
}

j_boolean_t CJoissManager::CheckUser(const j_char_t *pUserName, const j_char_t *pPasswd, j_int32_t nAuthType)
{
    j_int32_t nRet = J_OK;
	if ((nRet = OpenDB()) != J_OK)
		return nRet;

    const j_char_t *sql = "select pass_word from t_user where user_name='%s';";
    j_char_t sql_buff[256] = {0};
    sprintf(sql_buff, sql, pUserName);

	j_char_t **dbResult = NULL;
    j_int32_t nRow = 0;
	j_int32_t nColumn = 0;
	if (sqlite3_get_table(m_sqlite, sql_buff, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
    {
        if (memcmp(dbResult[nColumn], pPasswd, strlen(pPasswd)) == 0)
            return true;
    }
    return false;
}

const j_char_t *CJoissManager::GetResList()
{
    const j_char_t *sql_buff = "select id, res_name from t_resource;";
    j_char_t **dbResult = NULL;
	j_int32_t nRow = 0;
	j_int32_t nColumn = 0;
	TiXmlDocument *pXmlDoc = new TiXmlDocument();
	TiXmlElement *pRootElement = new TiXmlElement("Server");
	pXmlDoc->LinkEndChild(pRootElement);
	pRootElement->SetAttribute("id", "0");
	pRootElement->SetAttribute("ipAddr", "192.168.1.106");
	pRootElement->SetAttribute("desc", "视频主目录");
	TiXmlElement *pChannelElement = NULL;

	if (sqlite3_get_table(m_sqlite, sql_buff, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
	{
		for (j_int32_t i=1; i<=nRow; i++)
		{
		    pChannelElement = new TiXmlElement("Channel");
		    pRootElement->LinkEndChild(pChannelElement);
			for (j_int32_t j=0; j<nColumn; j++)
			{
				if (memcmp(dbResult[j], "id", strlen("id")) == 0)
					pChannelElement->SetAttribute("id", dbResult[j+i*nColumn]);
				else if (memcmp(dbResult[j], "res_name", strlen("res_name")) == 0)
                    pChannelElement->SetAttribute("desc", dbResult[j+i*nColumn]);
            }
		}
		TiXmlPrinter *pPrinter = new TiXmlPrinter();
		pXmlDoc->Accept(pPrinter);
		return pPrinter->CStr();
	}

    return NULL;
}

j_int32_t CJoissManager::GetRcdList(const j_char_t *pResid, j_time_t begin_time, j_time_t end_time, j_char_t *pDataBuff)
{
	int nOffset = 0;
	time_t begin = 0;
	time_t cur_begin = 0;
	time_t cur_end = 0;
	j_vec_file_info_t vecFileInfo;
	m_file.GetFilesByTime("/home/jorhy/vod", pResid, begin_time, end_time, vecFileInfo);
	j_vec_file_info_t::iterator it = vecFileInfo.begin();
	for(; it!=vecFileInfo.end(); ++it)
	{
		cur_begin = it->tStartTime;
		if (cur_end == 0)//初始化
		{
			begin = cur_begin;
			cur_end = it->tStoptime;
		}
		else if (cur_end - cur_begin > 5)
		{
			J_RcdTimeInfo *pInfo = (J_RcdTimeInfo *)(pDataBuff + nOffset);
			pInfo->begin_time = begin;
			pInfo->end_time = it->tStoptime; 
			nOffset += sizeof(J_RcdTimeInfo);
			cur_end = 0;
		}
		else
			cur_end = it->tStoptime;
	}
	J_RcdTimeInfo *pInfo = (J_RcdTimeInfo *)(pDataBuff + nOffset);
	pInfo->begin_time = begin;
	pInfo->end_time = cur_end; 
	nOffset += sizeof(J_RcdTimeInfo);
	
	return nOffset;
}

j_result_t CJoissManager::OpenDB()
{
	j_int32_t nRet = SQLITE_OK;
	if (m_sqlite == NULL)
		nRet = sqlite3_open("x_conf.db", &m_sqlite);

	if (nRet != SQLITE_OK)
		return J_DB_ERROR;

	return J_OK;
}
