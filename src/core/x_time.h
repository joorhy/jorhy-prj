#ifndef __X_TIME_H_
#define __X_TIME_H_
#include "j_type.h"
#include "x_singleton.h"

class JO_API CTime
{
public:
    CTime() {}

public:
	j_string_t GetLocalTime();
	j_uint64_t GetLocalTime(j_string_t &strTime);
	j_string_t GetLocalTimeASC();
	j_uint64_t GetLocalTime(j_int32_t) const;
	j_time_t ConvertToTime_t(const j_char_t *pLogTime);
	j_string_t GetDate();
	j_string_t GetDate(j_time_t nTime);
};
JO_DECLARE_SINGLETON(Time)

#endif //~__X_TIME_H_
