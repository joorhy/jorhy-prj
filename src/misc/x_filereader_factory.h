#ifndef __FILEREADERFACTORY_H_
#define __FILEREADERFACTORY_H_

#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakeFileReaderFun)(J_Obj *&, const char *pResid);

class JO_API CFileReaderFactory : public SingletonTmpl<CFileReaderFactory>
{
	typedef std::map<j_string_t, J_MakeFileReaderFun> FileReaderRegistMap;
	typedef std::map<j_socket_t, J_FileReader *> FileReaderMap;
public:
	CFileReaderFactory(int) {}
	~CFileReaderFactory() {}

protected:
    CFileReaderFactory() {}

public:
	///注册Filter类
	///@param[in] 	fileReaderType FileReader
	///@param[in] 	J_MakeFileReaderFun FileReader的构造函数
	///@return 		参考x_error_type.h
	int RegisterFileReader(const char *fileReaderType, J_MakeFileReaderFun pFun);

	J_FileReader *GetFileReader(j_socket_t nSocket, const char *pType, const char *pResid);
	void DelFileReader(j_socket_t nSocket);

private:
	FileReaderRegistMap m_fileReaderRegistMap;
	FileReaderMap m_fileReaderMap;
	J_OS::TLocker_t m_lock;
};

#endif // __FILEREADERFACTORY_H_
