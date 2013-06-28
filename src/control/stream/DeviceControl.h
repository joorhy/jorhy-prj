#ifndef __DEVICECONTROL_H_
#define __DEVICECONTROL_H_
#include "RecordMediaObj.h"
#include "x_timer.h"

class JO_API CDeviceControl
{
public:
	CDeviceControl();
	~CDeviceControl();

public:
	///录像控制接口
	int StartRecord(const char *pResid);
	int StopRecord(const char *pResid);

	///云台控制接口
	int PtzControl(const char *pResid, int nCmd, int nParam);

private:
	struct RecordInfo
	{
		CStreamRecord *pRecord;
		bool bPreRecord;
		int nCount;
		int nPreCount;
	};
	std::map<std::string, RecordInfo> m_recordMap;	//Resid 与 VideoRecord对象的映射关系
};
#endif //__DEVICECONTROL_H_
