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

bool CJoissManager::CheckUser(const char *pUserName, const char *pPasswd, int nAuthType)
{
    int nRet = J_OK;
	if ((nRet = OpenDB()) != J_OK)
		return nRet;

    const char *sql = "select pass_word from t_user where user_name='%s';";
    char sql_buff[256] = {0};
    sprintf(sql_buff, sql, pUserName);

	char **dbResult = NULL;
    int nRow = 0;
	int nColumn = 0;
	if (sqlite3_get_table(m_sqlite, sql_buff, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
    {
        if (memcmp(dbResult[nColumn], pPasswd, strlen(pPasswd)) == 0)
            return true;
    }
    return false;
}

const char *CJoissManager::GetResList()
{
    const char *sql_buff = "select id, res_name from t_resource;";
    char **dbResult = NULL;
	int nRow = 0;
	int nColumn = 0;
	TiXmlDocument *pXmlDoc = new TiXmlDocument();
	TiXmlElement *pRootElement = new TiXmlElement("Server");
	pXmlDoc->LinkEndChild(pRootElement);
	pRootElement->SetAttribute("id", "0");
	pRootElement->SetAttribute("ipAddr", "192.168.1.53");
	pRootElement->SetAttribute("desc", "视频主目录");
	TiXmlElement *pChannelElement = NULL;

	if (sqlite3_get_table(m_sqlite, sql_buff, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
	{
		for (int i=1; i<=nRow; i++)
		{
		    pChannelElement = new TiXmlElement("Channel");
		    pRootElement->LinkEndChild(pChannelElement);
			for (int j=0; j<nColumn; j++)
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

int CJoissManager::GetRcdList(const char *pResid, time_t begin_time, time_t end_time, char *pDataBuff)
{
	return 0;
}

int CJoissManager::OpenDB()
{
	int nRet = SQLITE_OK;
	if (m_sqlite == NULL)
		nRet = sqlite3_open("x_conf.db", &m_sqlite);

	if (nRet != SQLITE_OK)
		return J_DB_ERROR;

	return J_OK;
}
