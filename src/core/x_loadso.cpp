#include "x_loadso.h"
#include "x_errtype.h"
#include "x_log.h"
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>

CXLoadso::CXLoadso()
{

}

CXLoadso::~CXLoadso()
{

}

int CXLoadso::JoLoadSo()
{
    char currentPath[256] = {0};
    if (!getcwd(currentPath, 255))
    {
        J_OS::LOGERROR("CXLoadso::LoadSo getcwd error");
        return J_UNKNOW;
    }
    //LoadSo(currentPath, "plugins/access");
    //LoadSo(currentPath, "plugins/config");
	LoadSo(currentPath, "plugins");

    return J_OK;
}

int CXLoadso::JoUnloadSo()
{
    return J_OK;
}

int CXLoadso::LoadSo(const char *pPath, const char *subPath)
{
    char modPath[256] = {0};
    sprintf(modPath, "%s/%s", pPath, subPath);
    struct dirent *ent = NULL;
    DIR *pDir = NULL;
    pDir = opendir(modPath);
    if (pDir == NULL)
    {
        J_OS::LOGERROR("CXLoadso::LoadSo opendir error, dir = %s", modPath);
        return J_UNKNOW;
    }

    char modName[256] = {0};
    while ((ent = readdir(pDir)) != NULL)
    {
        memset(modName, 0, sizeof(modName));
        sprintf(modName, "./%s/%s", subPath, ent->d_name);
        if (strstr(modName, ".so") != NULL)
        {
            void *handle = dlopen(modName, RTLD_LAZY);
            if (handle == NULL)
            {
                J_OS::LOGINFO("CXLoadso::LoadSo dlopen, err = %s", dlerror());
                continue;
            }
            m_vecHandle.push_back(handle);
        }
    }
    closedir(pDir);

    return J_OK;
}
