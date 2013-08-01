/**
*  Copyright (c) 2013, 成都荣耀科技有限公司(http://www.ronyao.com/)
*  All rights reserved.
*
*  @file        MyBasicUsageEnvironment.h
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/24 17:17
*  @version     ver 1.0.0.1
*
*  @brief       live555模块错误信息打印
*  @note        无
*
*   v1.0.0.1    2013/07/24 17:17    完成基础代码
*/

#ifndef __MyBasicUsageEnvironment_head__
#define __MyBasicUsageEnvironment_head__

#include "BasicUsageEnvironment.hh"
#include <fstream>

using namespace std;

/** 记录日志开关 */
#define ERROR_TO_FILE_FLAG


/**
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/24 17:30
*  @class       CLive555ErrorToFile
*  @brief       记录Live555运行日志
*  @note        无
*/
class CLive555ErrorToFile :
	public BasicUsageEnvironment
{
public:
	static CLive555ErrorToFile* CreateNew(TaskScheduler& taskScheduler, string strErrorFile);

	virtual UsageEnvironment& operator<<(char const* str);
	virtual UsageEnvironment& operator<<(int i);
	virtual UsageEnvironment& operator<<(unsigned u);
	virtual UsageEnvironment& operator<<(double d);
	virtual UsageEnvironment& operator<<(void* p);

protected:
	CLive555ErrorToFile(TaskScheduler& taskScheduler, string strErrorFile);
	virtual ~CLive555ErrorToFile(void);

private:
	FILE * m_ErrFile;
};

#endif // __MyBasicUsageEnvironment_head__