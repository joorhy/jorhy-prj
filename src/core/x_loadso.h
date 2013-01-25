#ifndef __X_LOADSO_H_
#define __X_LOADSO_H_
#include <vector>

class CXLoadso
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
    typedef std::vector<void *> VecHandle;
    VecHandle m_vecHandle;
};

#endif // __X_LOADSO_H_
