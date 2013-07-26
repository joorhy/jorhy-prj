#ifndef __X_VOD_MANAGER_H_
#define __X_VOD_MANAGER_H_
#include "j_includes.h"

class JO_API CXVodManager
{
public:
	CXVodManager();
	~CXVodManager();

public:
	///查询历史文件信息
	///@param[in]		pResid 资源ID
	///@param[in]		begin_time 开始时间
	///@param[in]		end_time 结束时间
	///@param[out]	vecFileInfo 文件信息
	///@return			参见j_errtype.h
	j_result_t SearchVodFiles(const j_char_t *pResid, j_time_t begin_time, j_time_t end_time, j_vec_file_info_t &vecFileInfo);

	///统计历史文件信息
	///@param[in]		pResid 资源ID
	///@param[out]	begin_time 开始时间
	///@param[out]	end_time 结束时间
	///@param[out]	nSize 文件大小(单位KB)
	///@return			参见j_errtype.h
	j_result_t GetRecordInfo(const j_char_t *pResid, j_time_t &begin_time, j_time_t &end_time, j_int64_t &nSize);

	///统计录像资源信息
	///@param[in]		vecResid 录像文件资源ID
	///@return			参见j_errtype.h
	j_result_t GetRecordResid(j_vec_resid_t &vecResid);

	///删除录像文件
	///@param[in]		delRecordCtrl 录像资源信息
	///@return			参见j_errtype.h
	j_result_t DelFiles(J_DelRecordCtrl &delRecordCtrl);

private:
	void FillFileInfo(const char *pFileName, J_FileInfo &fileInfo);
	int SearchOneDayFiles(const j_char_t *pResid, const char *pDate, j_time_t begin_time, j_time_t end_time, j_vec_file_info_t &vecFileInfo);
	int DeleteFilesByResid(const j_char_t *pResid, j_time_t begin_time, j_time_t end_time);
	int DeleteDirectory(char *DirName);
};
JO_DECLARE_SINGLETON(XVodManager)
#endif //~__X_VOD_MANAGER_H_