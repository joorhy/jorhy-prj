#include "x_loadso.h"
#include "x_errtype.h"
#include "x_log.h"

CXLoadso::CXLoadso()
{

}

CXLoadso::~CXLoadso()
{

}

int CXLoadso::JoLoadSo()
{
    char currentPath[256] = {0};
#ifdef WIN32
	if (!GetCurrentDirectory(255, currentPath))  
#else
    if (!getcwd(currentPath, 255))
#endif
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
#ifdef WIN32
	WIN32_FIND_DATA FindFileData;  
	HANDLE hFind;  

	hFind = FindFirstFile(modPath, &FindFileData);  
	if (hFind == INVALID_HANDLE_VALUE)   
	{  
		J_OS::LOGERROR("CXFile::ListFiles FindFirstFile failed\n");  
		return J_UNKNOW;  
	}  

	char modName[256] = {0};
	do  
	{   
		memset(modName, 0, sizeof(modName));
		sprintf(modName, "./%s/%s", subPath, FindFileData.cFileName);
		if (strstr(modName, ".dll") != NULL)
		{
			j_module_t module;
			module.handle = LoadLibrary(modName);
			if (module.handle == j_invalid_module_val)
			{
				J_OS::LOGINFO("CXLoadso::LoadSo LoadLibrary, err = %s", GetLastError());
				continue;
			}
			m_vecHandle.push_back(module);
		}
	} while (FindNextFile(hFind, &FindFileData));  
	CloseHandle(hFind);
#else
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
			j_module_t module;
            module.handle = dlopen(modName, RTLD_LAZY);
            if (module.handle == j_invalid_module_val)
            {
                J_OS::LOGINFO("CXLoadso::LoadSo dlopen, err = %s", dlerror());
                continue;
            }
            m_vecHandle.push_back(module);
        }
    }
    closedir(pDir);
#endif

    return J_OK;
}
