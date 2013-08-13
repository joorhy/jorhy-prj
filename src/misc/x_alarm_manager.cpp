#include "x_alarm_manager.h"
#include "x_sdk.h"
#include "x_config.h"

JO_IMPLEMENT_SINGLETON(AlarmManager)

CAlarmManager::CAlarmManager()
{

}

CAlarmManager::~CAlarmManager()
{

}

j_result_t CAlarmManager::OnAlarm(const J_AlarmData &alarmData)
{
	return JoXSdk->NotifyAlarmInfo(alarmData, (j_char_t *)CXConfig::GetUrl());
}