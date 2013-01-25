#ifndef __JOISSMANAGER_H_
#define __JOISSMANAGER_H_
#include "j_includes.h"
#include "sqlite3.h"

class CJoissManager
{
public:
    CJoissManager();
    ~CJoissManager();

public:
    bool CheckUser(const char *pUserName, const char *pPasswd, int nAuthType = 0);
    const char *GetResList();
	int GetRcdList(const char *pResid, time_t begin_time, time_t end_time, char *pDataBuff);

private:
    int OpenDB();

private:
	sqlite3 *m_sqlite;
};

#endif // __JOISSMANAGER_H_
