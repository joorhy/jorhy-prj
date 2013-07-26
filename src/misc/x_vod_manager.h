#ifndef __X_VOD_MANAGER_H_
#define __X_VOD_MANAGER_H_
#include "j_includes.h"
#include "x_file.h"

class JO_API CXVodManager
{
public:
	CXVodManager();
	~CXVodManager();

public:
	///²éÑ¯ÀúÊ·ÎÄ¼þÐÅÏ¢
	///@param[in]		pResid ×ÊÔ´ID
	///@param[in]		begin_time ¿ªÊ¼Ê±¼ä
	///@param[in]		end_time ½áÊøÊ±¼ä
	///@param[out]	vecFileInfo ÎÄ¼þÐÅÏ¢
	///@return			²Î¼ûj_errtype.h
	j_result_t SearchVodFiles(const j_char_t *pResid, j_time_t begin_time, j_time_t end_time, j_vec_file_info_t &vecFileInfo);

	///Í³¼ÆÀúÊ·ÎÄ¼þÐÅÏ¢
	///@param[in]		pResid ×ÊÔ´ID
	///@param[out]	begin_time ¿ªÊ¼Ê±¼ä
	///@param[out]	end_time ½áÊøÊ±¼ä
	///@param[out]	nSize ÎÄ¼þ´óÐ¡(µ¥Î»KB)
	///@return			²Î¼ûj_errtype.h
	j_result_t GetRecordInfo(const j_char_t *pResid, j_time_t &begin_time, j_time_t &end_time, j_int64_t &nSize);

	///Í³¼ÆÂ¼Ïñ×ÊÔ´ÐÅÏ¢
	///@param[in]		vecResid Â¼ÏñÎÄ¼þ×ÊÔ´ID
	///@return			²Î¼ûj_errtype.h
	j_result_t GetRecordResid(j_vec_resid_t &vecResid);

	///É¾³ýÂ¼ÏñÎÄ¼þ
	///@param[in]		delRecordCtrl Â¼Ïñ×ÊÔ´ÐÅÏ¢
	///@return			²Î¼ûj_errtype.h
	j_result_t DelFiles(J_DelRecordCtrl &delRecordCtrl);

private:
	void FillFileInfo(const char *pFileName, J_FileInfo &fileInfo);
	int SearchOneDayFiles(const j_char_t *pResid, const char *pDate, j_time_t begin_time, j_time_t end_time, j_vec_file_info_t &vecFileInfo);
	int DeleteFilesByResid(const j_char_t *pResid, j_time_t begin_time, j_time_t end_time);
	int DeleteDirectory(char *DirName);
	
private:
	CXFile m_fileHelper;
};
JO_DECLARE_SINGLETON(XVodManager)
#endif //~__X_VOD_MANAGER_H_