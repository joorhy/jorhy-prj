#include "BTKCpuUseage.h"


BOOL BTKCpuInfo::Init()
{
	memset(&m_liOldIdleTime, 0, sizeof(LARGE_INTEGER));
	memset(&m_liOldSystemTime, 0, sizeof(LARGE_INTEGER));

	m_NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(
		GetModuleHandle("ntdll"),
		"NtQuerySystemInformation");

	if (!m_NtQuerySystemInformation)
		return FALSE;

	// get number of processors in the system
	m_status = m_NtQuerySystemInformation(SystemBasicInformation, &m_SysBaseInfo, sizeof(SYSTEM_BASIC_INFORMATION), NULL);
	if (m_status != NO_ERROR)
		return FALSE;

	return TRUE;
}

BOOL BTKCpuInfo::GetInfo(UINT &nInfo)
{
	// get new system time
	m_status = m_NtQuerySystemInformation(SystemTimeInformation, &m_SysTimeInfo, sizeof(SYSTEM_TIME_INFORMATION), NULL);
	if (m_status!=NO_ERROR)
		return FALSE;

	// get new CPU's idle time
	m_status = m_NtQuerySystemInformation(SystemPerformanceInformation, &m_SysPerfInfo ,sizeof(SYSTEM_PERFORMANCE_INFORMATION), NULL);
	if (m_status != NO_ERROR)
		return FALSE;

	// if it's a first call - skip it
	if (m_liOldIdleTime.QuadPart != 0)
	{
		// CurrentValue = NewValue - OldValue
		m_dbIdleTime = Li2Double(m_SysPerfInfo.liIdleTime) - Li2Double(m_liOldIdleTime);
		m_dbSystemTime = Li2Double(m_SysTimeInfo.liKeSystemTime) - Li2Double(m_liOldSystemTime);

		// CurrentCpuIdle = IdleTime / SystemTime
		m_dbIdleTime = m_dbIdleTime / m_dbSystemTime;

		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
		m_dbIdleTime = 100.0 - m_dbIdleTime * 100.0 / (double)m_SysBaseInfo.bKeNumberProcessors;
		nInfo = (UINT)m_dbIdleTime;
	}

	// store new CPU's idle and system time
	m_liOldIdleTime = m_SysPerfInfo.liIdleTime;
	m_liOldSystemTime = m_SysTimeInfo.liKeSystemTime;

	return TRUE;
}