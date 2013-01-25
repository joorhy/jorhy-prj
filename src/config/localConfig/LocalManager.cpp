#include "LocalManager.h"

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

int CLocalManager::ListDevices(std::vector<J_DeviceInfo> &devList)
{
	int nRet = J_OK;
	if ((nRet = OpenDB()) != J_OK)
		return nRet;

	const char *sql = "select * from t_device;";
	char **dbResult = NULL;
	int nRow = 0;
	int nColumn = 0;
	if (sqlite3_get_table(m_sqlite, sql, &dbResult, &nRow, &nColumn, NULL) == SQLITE_OK)
	{
		for (int i=1; i<=nRow; i++)
		{
			J_DeviceInfo devInfo = {0};
			for (int j=0; j<nColumn; j++)
			{
				if (memcmp(dbResult[j], "id", strlen("id")) == 0)
					devInfo.devId = atoi(dbResult[j+i*nColumn]);
				else if (memcmp(dbResult[j], "ip_addr", strlen("ip_addr")) == 0)
					memcpy(devInfo.devIp, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
				else if (memcmp(dbResult[j], "port", strlen("port")) == 0)
					devInfo.devPort = (short)atoi(dbResult[j+i*nColumn]);
				else if (memcmp(dbResult[j], "dev_type", strlen("dev_type")) == 0)
					memcpy(devInfo.devType, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
				else if (memcmp(dbResult[j], "user_name", strlen("user_name")) == 0)
					memcpy(devInfo.userName, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
				else if (memcmp(dbResult[j], "pass_wd", strlen("pass_wd")) == 0)
					memcpy(devInfo.passWd, dbResult[j+i*nColumn], strlen(dbResult[j+i*nColumn]));
			}
			devInfo.devStatus = J_DevBroken;
			devList.push_back(devInfo);
		}

		return J_OK;
	}

	return J_DB_ERROR;
}

int CLocalManager::GetChannelInfo(const char *channelId, J_ChannelInfo &channelInfo)
{
	int nRet = J_OK;
	if ((nRet = OpenDB()) != J_OK)
		return nRet;


	memset(&channelInfo, 0, sizeof(channelInfo));
	const char *sql = "select dev_id,cha_num from t_channel where res_id=%s";
	char sql_buff[128] = {0};
	sprintf(sql_buff, sql, channelId);
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
					channelInfo.devId = atoi(dbResult[j+i*nColumn]);
				else if (memcmp(dbResult[j], "cha_num", strlen("cha_num")) == 0)
					channelInfo.channelNum = atoi(dbResult[j+i*nColumn]);
			}
		}
		return J_OK;
	}

	return J_DB_ERROR;
}

int CLocalManager::GetRecordInfo(J_RecordInfo &recordInfo)
{
    memset (&recordInfo, 0, sizeof(recordInfo));
    memcpy(recordInfo.vodPath, "file://$HOME/vod", strlen("file://$HOME/vod"));
    recordInfo.timeInterval = 120;

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
