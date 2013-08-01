#ifndef __X_ALARM_MANAGER_H_
#define __X_ALARM_MANAGER_H_
#include "j_includes.h"

class JO_API CAlarmManager
{
public:
	CAlarmManager();
	~CAlarmManager();

public:
	///发送报警时间
	///param[in]	alarmData 报警数据
	///@return 	参见x_error_type.h
	j_result_t OnAlarm(const J_AlarmData &alarmData);	
};

JO_DECLARE_SINGLETON(AlarmManager)

#endif//~__X_ALARM_MANAGER_H_