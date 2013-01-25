#include "MCManager.h"
#include "tinyxml.h"

CMCManager::CMCManager()
{
    m_conn = NULL;
}

CMCManager::~CMCManager()
{
	if (m_conn != NULL)
	{
		mysql_close(m_conn);
		m_conn = NULL;
	}
}

bool CMCManager::CheckUser(const char *pUserName, const char *pPasswd, int nAuthType)
{
    int nRet = J_OK;
	if ((nRet = OpenDB()) != J_OK)
		return nRet;

    const char *sql = "select passwd from user where uname='%s';";
    char sql_buff[256] = {0};
    sprintf(sql_buff, sql, pUserName);
	
	if (mysql_query(m_conn, sql_buff))
		return false;

	MYSQL_RES *dbResult = mysql_use_result(m_conn);
	MYSQL_ROW dbRow = NULL;
	while ((dbRow = mysql_fetch_row(dbResult)) != NULL)
	{
		if (memcmp(dbRow[0], pPasswd, strlen(pPasswd)) == 0)
		{
			mysql_free_result(dbResult);
            return true;
		}
	}
	mysql_free_result(dbResult);

    return false;
}

const char *CMCManager::GetResList()
{
    const char *sql_buff = "select id, type, name from resource;";
	TiXmlDocument *pXmlDoc = new TiXmlDocument();
	TiXmlDeclaration *pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
	TiXmlElement *pRootElement = new TiXmlElement("Server");
	pXmlDoc->LinkEndChild(pDecl);
	pXmlDoc->LinkEndChild(pRootElement);
	pRootElement->SetAttribute("id", "0");
	pRootElement->SetAttribute("ipAddr", "192.168.1.53");
	pRootElement->SetAttribute("desc", "视频主目录");
	TiXmlElement *pChannelElement = NULL;

	if (mysql_query(m_conn, sql_buff))
		return NULL;
		
	MYSQL_RES *dbResult = mysql_use_result(m_conn);
	MYSQL_ROW dbRow = NULL;
	
	//int nColumn = mysql_num_fields(dbResult);
	while ((dbRow = mysql_fetch_row(dbResult)) != NULL)
	{
		if (memcmp(dbRow[1], "1", strlen("1")) == 0)
		{
			pChannelElement = new TiXmlElement("Channel");
			pRootElement->LinkEndChild(pChannelElement);
			pChannelElement->SetAttribute("id", dbRow[0]);
			pChannelElement->SetAttribute("desc", dbRow[2]);
		}
	}
	TiXmlPrinter *pPrinter = new TiXmlPrinter();
	pXmlDoc->Accept(pPrinter);
	
	return pPrinter->CStr();
}

int CMCManager::GetRcdList(const char *pResid, time_t begin_time, time_t end_time, char *pDataBuff)
{
	const char *sql = "select stime, etime from video where resid=%s and stime>=%u and etime<=%u;";
    char sql_buff[256] = {0};
    sprintf(sql_buff, sql, pResid, begin_time, end_time);
	fprintf(stderr, sql_buff);
	
	if (mysql_query(m_conn, sql_buff))
		return NULL;
		
	MYSQL_RES *dbResult = mysql_use_result(m_conn);
	MYSQL_ROW dbRow = NULL;
	
	int nOffset = 0;
	time_t begin = 0;
	time_t cur_begin = 0;
	time_t cur_end = 0;
	while ((dbRow = mysql_fetch_row(dbResult)) != NULL)
	{
		cur_begin = atoll(dbRow[0]);
		if (cur_end == 0)//初始化
		{
			begin = cur_begin;
			cur_end = atoll(dbRow[1]);
		}
		else if (cur_end - cur_begin > 5)
		{
			J_FileInfo *pInfo = (J_FileInfo *)(pDataBuff + nOffset);
			pInfo->tStartTime = begin;
			pInfo->tStoptime = atoll(dbRow[1]); 
			nOffset += sizeof(J_FileInfo);
			cur_end = 0;
		}
		else
			cur_end = atoll(dbRow[1]);
	}
	J_FileInfo *pInfo = (J_FileInfo *)(pDataBuff + nOffset);
	pInfo->tStartTime = begin;
	pInfo->tStoptime = cur_end; 
	nOffset += sizeof(J_FileInfo);
	
	return nOffset;
}

int CMCManager::OpenDB()
{
	if (m_conn == NULL)
	{
		m_conn = mysql_init(NULL);
		/* Connect to database*/
		if (!mysql_real_connect(m_conn, "192.168.1.10", "root", "jennyzhan", "ivs_new", 0, NULL, 0))
		{
			return J_DB_ERROR;
		}
		mysql_set_character_set(m_conn, "utf8");
	}

	return J_OK;
}
