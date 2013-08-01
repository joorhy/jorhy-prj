#include "x_alarm_manager.h"

JO_IMPLEMENT_SINGLETON(AlarmManager)

CAlarmManager::CAlarmManager()
{

}

CAlarmManager::~CAlarmManager()
{

}

j_result_t CAlarmManager::OnAlarm(const J_AlarmData &alarmData)
{
	return J_OK;
}