#ifndef __JOISSMANAGER_H_
#define __JOISSMANAGER_H_
#include "j_includes.h"
#include "DeviceControl.h"
#include "sqlite3.h"

class JO_API CJoissManager
{
public:
    CJoissManager();
    ~CJoissManager();

public:
    j_boolean_t CheckUser(const j_char_t *pUserName, const j_char_t *pPasswd, j_int32_t nAuthType = 0);
    const j_char_t *GetResList();
	j_int32_t GetRcdList(const j_char_t *pResid, j_time_t begin_time, j_time_t end_time, j_char_t *pDataBuff);

private:
    j_int32_t OpenDB();

private:
	sqlite3 *m_sqlite;
	CXFile m_file;
};

#endif // __JOISSMANAGER_H_
