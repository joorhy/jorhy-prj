#include "LocalManager.h"
#include "RecoderManager.h"

JO_IMPLEMENT_INTERFACE(Manager, "local", CLocalManager::Maker)

CLocalManager::CLocalManager()
{
	m_sqlite = NULL;
}

CLocalManager::~CLocalManager()
{
	if (m_sqlite != NULL)
	{
		sqlite3_close(m_sqlite);
		m_sqlite = NULL;
	}
}

j_result_t CLocalManager::GetResourceInfo(ResourceMap &resInfo)
{
	int nRet = J_OK;
	if ((nRet = OpenDB()) != J_OK)
		return nRet;

	const char *sql = "select * from t_device;";
	char **dbResult = NULL;
	int nRow = 0;
	int nColumn = 0;
	char **errMessage = NULL;
	if (sqlite3_get_table(m_sqlite, sql, &dbResult, &nRow, &nColumn, errMessage) == SQLITE_OK)
	{
		for (int i=1; i<=nRow; i++)
		{
			J_ResourceInfo resourceInfo = {0};
			for (int j=0; j<nColumn; j++)
			{
				if (memcmp(dbResult[j], "id", strlen("id")) == 0)
					resourceInfo.devInfo.devId = atoi(dbResult[j+i*nColumn]);
				else if (memcmp(dbResult[j], "ip_addr", strlen("ip_addr")) == 0)
					memcpy(resourceInfo.devInfo.devIp, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
				else if (memcmp(dbResult[j], "port", strlen("port")) == 0)
					resourceInfo.devInfo.devPort = (short)atoi(dbResult[j+i*nColumn]);
				else if (memcmp(dbResult[j], "dev_type", strlen("dev_type")) == 0)
					memcpy(resourceInfo.devInfo.devType, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
				else if (memcmp(dbResult[j], "user_name", strlen("user_name")) == 0)
					memcpy(resourceInfo.devInfo.userName, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
				else if (memcmp(dbResult[j], "pass_wd", strlen("pass_wd")) == 0)
					memcpy(resourceInfo.devInfo.passWd, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
			}
			resourceInfo.devInfo.devStatus = jo_dev_broken;
			
			char sql2_buff[128] = {0};
			const char *sql2 = "select cha_num, res_id from t_channel where dev_id=%d;";
			sprintf(sql2_buff, sql2, resourceInfo.devInfo.devId);
			char **dbResult2 = NULL;
			int nRow2 = 0;
			int nColumn2 = 0;
			char **errMessage2 = NULL;
			if (sqlite3_get_table(m_sqlite, sql2_buff, &dbResult2, &nRow2, &nColumn2, errMessage2) == SQLITE_OK)
			{
				for (int i=1; i<=nRow2; i++)
				{
					for (int j=0; j<nColumn2; j++)
					{
						if (memcmp(dbResult2[j], "cha_num", strlen("cha_num")) == 0)
							resourceInfo.chNum = atoi(dbResult2[j+i*nColumn2]);
						else if (memcmp(dbResult2[j], "res_id", strlen("res_id")) == 0)
							memcpy(resourceInfo.resid, dbResult2[j+i*nColumn2], strlen(dbResult2[j+i*nColumn2]));
						resourceInfo.streamType = 0;
					}
				}
				resInfo[resourceInfo.resid] = resourceInfo;
			}
		}

		return J_OK;
	}

	return J_DB_ERROR;
}

int CLocalManager::GetChannelInfo(const char *pResid, J_ResourceInfo &resInfo)
{
	int nRet = J_OK;
	if ((nRet = OpenDB()) != J_OK)
		return nRet;


	memset(&resInfo, 0, sizeof(resInfo));
	const char *sql = "select dev_id,cha_num from t_channel where res_id=%s";
	char sql_buff[128] = {0};
	sprintf(sql_buff, sql, pResid);
	char **dbResult = NULL;
	int nRow = 0;
	int nColumn = 0;
	if (sqlite3_get_table(m_sqlite, sql_buff, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
	{
		for (int i=1; i<=nRow; i++)
		{
			for (int j=0; j<nColumn; j++)
			{
				if (memcmp(dbResult[j], "dev_id", strlen("dev_id")) == 0)
					resInfo.devInfo.devId = atoi(dbResult[j+i*nColumn]);
				else if (memcmp(dbResult[j], "cha_num", strlen("cha_num")) == 0)
					resInfo.chNum = atoi(dbResult[j+i*nColumn]);
			}
		}
		return J_OK;
	}

	return J_DB_ERROR;
}

int CLocalManager::StartRecord()
{
	const j_char_t *sql_buff = "select res_id,res_rcd_type from t_channel;";
    j_char_t **dbResult = NULL;
	j_int32_t nRow = 0;
	j_int32_t nColumn = 0;
	
	if (sqlite3_get_table(m_sqlite, sql_buff, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
	{
		for (j_int32_t i=1; i<=nRow; i++)
		{
			if (atoi(dbResult[i*nColumn + 1]) == jo_rcd_auto)
			{
				m_deviceControl.StartRecord(dbResult[i*nColumn]);
			}
		}
	}
	JoRecoderManager->Single();
	
	return J_OK;
}

int CLocalManager::StopRecord()
{
	const j_char_t *sql_buff = "select res_id,res_rcd_type from t_channel;";
    j_char_t **dbResult = NULL;
	j_int32_t nRow = 0;
	j_int32_t nColumn = 0;
	
	if (sqlite3_get_table(m_sqlite, sql_buff, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
	{
		for (j_int32_t i=1; i<=nRow; i++)
		{
			if (atoi(dbResult[i*nColumn + 1]) == jo_rcd_auto)
			{
				m_deviceControl.StopRecord(dbResult[i*nColumn]);
			}
		}
	}
	return J_OK;
}

int CLocalManager::OpenDB()
{
	int nRet = SQLITE_OK;
	if (m_sqlite == NULL)
		nRet = sqlite3_open("x_conf.db", &m_sqlite);

	if (nRet != SQLITE_OK)
		return J_DB_ERROR;

	return J_OK;
}
