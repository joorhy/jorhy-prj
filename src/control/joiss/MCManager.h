#ifndef __MCMANAGER_H_
#define __MCMANAGER_H_
#include "j_includes.h"
#include <mysql/mysql.h>

class CMCManager
{
public:
    CMCManager();
    ~CMCManager();

public:
    bool CheckUser(const char *pUserName, const char *pPasswd, int nAuthType = 0);
    const char *GetResList();
	int GetRcdList(const char *pResid, time_t begin_time, time_t end_time, char *pDataBuff);

private:
    int OpenDB();

private:
	MYSQL *m_conn;
};

#endif // __MCMANAGER_H_
