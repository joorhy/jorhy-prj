#ifndef __X_LOADSO_H_
#define __X_LOADSO_H_
#include "j_common.h"

class JO_API CXLoadso
{
public:
    CXLoadso();
    ~CXLoadso();

public:
    int JoLoadSo();
    int JoUnloadSo();

private:
    int LoadSo(const char *pPath, const char *subPath);

private:
    typedef std::vector<j_module_t> VecHandle;
    VecHandle m_vecHandle;
};

#endif // __X_LOADSO_H_
