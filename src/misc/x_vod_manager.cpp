#include "x_vod_manager.h"
#include "x_config.h"
#include "x_time.h"

JO_IMPLEMENT_SINGLETON(XVodManager)

CXVodManager::CXVodManager()
{

}

CXVodManager::~CXVodManager()
{

}

j_result_t CXVodManager::GetRecordInfo(const j_char_t *pResid, j_time_t &begin_time, j_time_t &end_time, j_int64_t &nSize)
{
	j_vec_file_info_t vecFileInfo;
	const char *pDir = CXConfig::GetVodPath();
	j_char_t file_name[256] = {0};

	begin_time = 0xFFFFFFFFFFFFFFFF;
	end_time = 0;
	nSize = 0;

#ifdef WIN32
	WIN32_FIND_DATA FindFileData;  
	HANDLE hFind;  

	sprintf(file_name, "%s/%s/*.*", pDir, pResid);
	hFind = FindFirstFile(file_name, &FindFileData);  
	if (hFind == INVALID_HANDLE_VALUE)   
	{  
		J_OS::LOGERROR("CXFile::GetRecordInfo FindFirstFile failed\n");  
		return J_UNKNOW;  
	}  
	
	do  
	{   
		if (memcmp(FindFileData.cFileName, ".", 1) != 0 
			&& memcmp(FindFileData.cFileName, "..", 2) != 0)
		{
			vecFileInfo.clear();
			SearchOneDayFiles(pResid, FindFileData.cFileName, 0, 0xFFFFFFFFFFFFFFFF, vecFileInfo);
			j_vec_file_info_t::iterator it = vecFileInfo.begin();
			for (; it!=vecFileInfo.end(); ++it)
			{
				if (it->tStartTime < begin_time)
					begin_time = it->tStartTime;
				if (it->tStoptime > end_time);
					end_time = it->tStoptime;
				nSize += it->nFileSize;
			}
		}
	} while (FindNextFile(hFind, &FindFileData));  
	FindClose(hFind);
#else
	DIR *dirPointer = NULL;
	struct dirent *entry;
	sprintf(file_name, "%s/%s", pDir, pResid);
	if ((dirPointer = opendir(file_name)) == NULL)
	{
		J_OS::LOGERROR("CXFile::ListFiles opendir error");
		return J_UNKNOW;
	}

	while ((entry = readdir(dirPointer)) != NULL)
	{
		if (memcmp(FindFileData.cFileName, ".", 1) != 0 
			&& memcmp(FindFileData.cFileName, "..", 2) != 0)
		{
			vecFileInfo.clear();
			SearchOneDayFiles(pResid, FindFileData.cFileName, 0, 0xFFFFFFFFFFFFFFFF, vecFileInfo);
			j_vec_file_info_t::iterator it = vecFileInfo.begin();
			for (; it!=vecFileInfo.end(); ++it)
			{
				if (it->tStartTime < begin_time)
					begin_time = it->tStartTime;
				if (it->tStoptime > end_time);
				end_time = it->tStoptime;
				nSize += it->nFileSize;
			}
		}
	}
	closedir(dirPointer);
#endif

	return J_OK;
}

j_result_t CXVodManager::SearchVodFiles(const j_char_t *pResid, j_time_t begin_time, j_time_t end_time, j_vec_file_info_t &vecFileInfo)
{
	j_string_t strBeginDate = JoTime->GetDate(begin_time);
	j_string_t strEndDate = JoTime->GetDate(end_time);
	SearchOneDayFiles(pResid, strBeginDate.c_str(), begin_time, end_time, vecFileInfo);
	if (strBeginDate != strEndDate)
		SearchOneDayFiles(pResid, strEndDate.c_str(), begin_time, end_time, vecFileInfo);

	return J_OK;
}

j_result_t CXVodManager::GetRecordResid(j_vec_resid_t &vecResid)
{
	const char *pDir = CXConfig::GetVodPath();
	j_char_t file_name[256] = {0};
#ifdef WIN32
	WIN32_FIND_DATA FindFileData;  
	HANDLE hFind;  

	sprintf(file_name, "%s/*.*", pDir);
	hFind = FindFirstFile(file_name, &FindFileData);  
	if (hFind == INVALID_HANDLE_VALUE)   
	{  
		J_OS::LOGERROR("CXFile::GetRecordInfo FindFirstFile failed\n");  
		return J_UNKNOW;  
	}  

	do  
	{   
		if (memcmp(FindFileData.cFileName, ".", 1) != 0 
			&& memcmp(FindFileData.cFileName, "..", 2) != 0)
		{
			vecResid.push_back(FindFileData.cFileName);
		}
	} while (FindNextFile(hFind, &FindFileData));  
	FindClose(hFind);
#else
	DIR *dirPointer = NULL;
	struct dirent *entry;
	sprintf(file_name, "%s", pDir);
	if ((dirPointer = opendir(file_name)) == NULL)
	{
		J_OS::LOGERROR("CXFile::ListFiles opendir error");
		return J_UNKNOW;
	}

	while ((entry = readdir(dirPointer)) != NULL)
	{
		if (memcmp(FindFileData.cFileName, ".", 1) != 0 
			&& memcmp(FindFileData.cFileName, "..", 2) != 0)
		{
			vecResid.push_back(FindFileData.cFileName);
		}
	}
	closedir(dirPointer);
#endif
	return J_OK;
}

void CXVodManager::FillFileInfo(const char *pFileName, J_FileInfo &fileInfo)
{
	fileInfo.fileName = pFileName;
	const char *p = pFileName;
	const char *p2 = strstr(p, "_");
	if (p2 != NULL)
	{
		fileInfo.tStartTime = atoi(p2 + 1);
		
		p = p2 + 1;
		p2 = strstr(p, "_");
		if (p2 != NULL)
			fileInfo.tStoptime = atoi(p2 + 1);
	}
}

int CXVodManager::SearchOneDayFiles(const j_char_t *pResid, const char *pDate, j_time_t begin_time, j_time_t end_time, j_vec_file_info_t &vecFileInfo)
{
	const char *pDir = CXConfig::GetVodPath();
	j_char_t file_name[256] = {0};
#ifdef WIN32
	WIN32_FIND_DATA FindFileData;  
	HANDLE hFind;  

	sprintf(file_name, "%s/%s/%s/*.*", pDir, pResid, pDate);
	hFind = FindFirstFile(file_name, &FindFileData);  
	if (hFind == INVALID_HANDLE_VALUE)   
	{  
		J_OS::LOGERROR("CXFile::ListFiles FindFirstFile failed\n");  
		return J_UNKNOW;  
	}  

	J_FileInfo fileInfo;
	do  
	{   
		if (memcmp(FindFileData.cFileName, pResid, strlen(pResid)) == 0)
		{
			fileInfo.nFileSize = (FindFileData.nFileSizeHigh << 32) + FindFileData.nFileSizeLow;
			FillFileInfo(FindFileData.cFileName, fileInfo);
			if ((fileInfo.tStartTime >= begin_time && fileInfo.tStartTime <= end_time)
				|| (fileInfo.tStoptime >= begin_time && fileInfo.tStoptime <= end_time))
			{
				vecFileInfo.push_back(fileInfo);
			}
		}
	} while (FindNextFile(hFind, &FindFileData));  
	FindClose(hFind);
#else
	DIR *dirPointer = NULL;
	struct dirent *entry;
	sprintf(file_name, "%s/%s/%s", pDir, pResid, pDate);
	if ((dirPointer = opendir(file_name)) == NULL)
	{
		J_OS::LOGERROR("CXFile::ListFiles opendir error");
		return J_UNKNOW;
	}

	while ((entry = readdir(dirPointer)) != NULL)
	{
		if (memcmp(entry->d_name, pResid, strlen(pResid)) == 0)
		{
			fileInfo.nFileSize = (FindFileData.nFileSizeHigh << 32) + FindFileData.nFileSizeLow;
			FillFileInfo(entry->d_name, fileInfo);
			if ((fileInfo.tStartTime >= begin_time && fileInfo.tStartTime <= end_time)
				|| (fileInfo.tStoptime >= begin_time && fileInfo.tStoptime <= end_time))
			{
				vecFileInfo.push_back(fileInfo);
			}
		}
	}
	closedir(dirPointer);
#endif
	vecFileInfo.sort();

	return J_OK;
}