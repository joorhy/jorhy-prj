#ifndef __X_LOGIN_H_
#define __X_LOGIN_H_

class CXLogin
{
public:
    CXLogin(const char *pAddr, int nPort = 6000);
    ~CXLogin();

public:
    bool CheckUser(const char *pUserName, const char *pPasswd, int nAuthType = 0);
};
#endif // __X_LOGIN_H_
