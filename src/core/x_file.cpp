#include "x_file.h"
#include "x_log.h"
#include "x_errtype.h"
#include "x_time.h"
#include "j_common.h"

CXFile::CXFile()
{

}

CXFile::~CXFile()
{

}

char *CXFile::GetVodDir(const char *pFrl, char *pDir)
{
#ifdef WIN32
	CreateDir((char *)pFrl);
	strncpy(pDir, pFrl, 128);
	return pDir;
#else
	char *p = NULL;
	char *p2 = NULL;
	FILE *fCheck = NULL;
	FILE *fCreate = NULL;
	if ((p = strstr(const_cast<char *>(pFrl), "nfs://")) != NULL)
	{
		p2 = p + strlen("nfs://");

		char checkBuff[1024] = {0};
		sprintf(checkBuff, "df /mnt/vod | grep %s", p2);

		fCheck = popen(checkBuff, "r");
		memset(checkBuff, 0, sizeof(checkBuff));
		fgets(checkBuff, sizeof(checkBuff), fCheck);

		if (strstr(checkBuff, p2) == NULL)
		{
			char nsfCmd[128] = {0};
			sprintf(nsfCmd, "sudo mount -t nfs %s /mnt", p2);

			fCreate = popen(nsfCmd, "w");
			//J_OS::LOGINFO("CVideoRecord::GetVodDir");
		}
		sprintf(pDir, "%s", "/mnt");
	}
	else if ((p = strstr(const_cast<char *>(pFrl), "file://")) != NULL)
	{
		p2 = p + strlen("file://");
		if (strstr(p2, "$HOME"))
		{
			char userDir[128] = {0};
			fCheck = popen("echo $HOME", "r");
			fgets(userDir, sizeof(userDir), fCheck);
			//J_OS::LOGINFO("CVideoRecord::GetVodDir");

			if (userDir[strlen(userDir) - 1] == '\n')
				userDir[strlen(userDir) - 1] = '\0';
			sprintf(pDir, "%s%s", userDir, p2 + 5);
		}
		else
		{
			sprintf(pDir, "%s", p2);
		}
	}
	if (fCheck)
		pclose(fCheck);

	if (fCreate)
		pclose(fCreate);

	return pDir;
#endif
}

int CXFile::CreateDir(char *pDir)
{
	char *p = strstr(pDir, "/");
	char *p2 = p;

	if (p2 == NULL)
		return J_UNKNOW;

	while ((p2 = p2 + 1) != NULL)
	{
		p2 = strstr(p2, "/");
		if (p2)
		{
			char vodDir[128] = {0};
			strncpy(vodDir, p, p2 - p);
#ifdef WIN32
			if (_access(vodDir, 0) != 0)
				CreateDirectory(vodDir, NULL);
#else
			if (access(vodDir, F_OK) != 0)
			{
				if (mkdir(vodDir, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
				{
					J_OS::LOGERROR("CXFile::CreateDir mkdir error");
					return J_FILE_ERROR;
				}
			}
#endif
		}
		else
		{
#ifdef WIN32
			if (_access(pDir, 0) != 0)
				CreateDirectory(pDir, NULL);
#else
			if (access(pDir, F_OK) != 0)
			{
				if (mkdir(pDir, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
				{
					J_OS::LOGERROR("CXFile::CreateDir mkdir error");
					return J_FILE_ERROR;
				}
			}
#endif
			break;
		}
	}

	return J_OK;
}

int CXFile::ListFiles(j_char_t *pDir, j_vec_str_t &fileVec, const j_char_t *pResid)
{
#ifdef WIN32
	WIN32_FIND_DATA FindFileData;  
	HANDLE hFind;  
	
	j_char_t file_name[256] = {0};
	sprintf(file_name, "%s/%s*.*", pDir, pResid);
	hFind = FindFirstFile(file_name, &FindFileData);  
	if (hFind == INVALID_HANDLE_VALUE)   
	{  
		J_OS::LOGERROR("CXFile::ListFiles FindFirstFile failed\n");  
		return J_UNKNOW;  
	}  
 
	do  
	{   
		if (pResid == NULL)
		{
			fileVec.push_back(FindFileData.cFileName);
		}
		else
		{
			if (memcmp(FindFileData.cFileName, pResid, strlen(pResid)) == 0)
				fileVec.push_back(FindFileData.cFileName);
		}
	} while (FindNextFile(hFind, &FindFileData));  
	FindClose(hFind);
#else
	DIR *dirPointer = NULL;
	struct dirent *entry;

	if ((dirPointer = opendir(pDir)) == NULL)
	{
		J_OS::LOGERROR("CXFile::ListFiles opendir error");
		return J_UNKNOW;
	}

	while ((entry = readdir(dirPointer)) != NULL)
	{
		if (pResid == NULL)
		{
			fileVec.push_back(entry->d_name);
		}
		else
		{
			if (memcmp(entry->d_name, pResid, strlen(pResid)) == 0)
				fileVec.push_back(entry->d_name);
		}
	}
	closedir(dirPointer);
#endif

	sort(fileVec.begin(), fileVec.end());
	return J_OK;
}

int CXFile::RenameFile(const char *oldName, const char *newDir, const char *newName)
{
#ifdef WIN32
	if(_access(oldName, 0) == 0)
	{ 
		CreateDir((char *)newDir);
		if(rename(oldName, newName) != 0)
		{ 
			J_OS::LOGINFO("CXFile::RenameFile Error");
			return J_FILE_ERROR;
		} 
	}  
#else
    FILE *fRename = NULL;
    char cmdBuff[1024] = {0};
    sprintf(cmdBuff, "mv %s %s", oldName, newName);
    fRename = popen(cmdBuff, "r");
    if (fRename)
        pclose(fRename);
#endif

    return J_OK;
}

int CXFile::DelFile(const j_char_t *filePath, const j_char_t *fileName)
{
#ifdef WIN32
	j_char_t full_name[256] = {0};
	sprintf(full_name, "%s/%s", filePath, fileName);
	if(_access(full_name, 0) != 0)
	{ 
		SetFileAttributes(full_name, 0); 
		if(!DeleteFile(full_name))
		{
			J_OS::LOGINFO("CXFile::DelFile ERROR");
			return J_FILE_ERROR;
		}
	}
#else
    FILE *fRename = NULL;
    char cmdBuff[1024] = {0};
    sprintf(cmdBuff, "rm %s/%s", filePath, fileName);
    fRename = popen(cmdBuff, "r");
    if (fRename)
        pclose(fRename);
#endif

    return J_OK;
}

int CXFile::DeltmpByResid(const char *pDir, const char *pResid)
{
    j_vec_str_t tmpFileVec;
    ListFiles((char *)pDir, tmpFileVec);
    j_vec_str_t::iterator it = tmpFileVec.begin();
    for (; it!=tmpFileVec.end(); it++)
    {
        if (memcmp(it->c_str(), pResid, strlen(pResid)) == 0)
        {
            DelFile(pDir, it->c_str());
        }
    }

    return J_OK;
}

int CXFile::GetFilesByTime(const char *pDir, const char *pResid, time_t begin_time, time_t end_time, j_vec_file_info_t &vecFileInfo)
{
	j_vec_str_t fileVec;
	ListFiles((char *)pDir, fileVec, pResid);
	j_vec_str_t::iterator it = fileVec.begin();
	j_string_t strBeginTime;
	j_string_t strEndTime;
	j_int32_t nPos1;
	j_int32_t nPos2;
	for (; it!=fileVec.end(); ++it)
	{
		nPos1 = it->find_first_of('_');
		nPos2 = it->find_last_of('_');
		if (nPos1 != j_string_t::npos && nPos2 != j_string_t::npos)
		{
			strBeginTime = it->substr(nPos1 + 1, 17);
			strEndTime = it->substr(nPos2 + 1, 17);
			J_FileInfo info = {0};
			info.tStartTime = JoTime->ConvertToTime_t(strBeginTime.c_str());
			info.tStoptime = JoTime->ConvertToTime_t(strEndTime.c_str());
			info.fileName = *it;
			
			vecFileInfo.push_back(info);
		}
		 
	}
	return J_OK;
}