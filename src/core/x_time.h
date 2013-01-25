#ifndef __X_TIME_H_
#define __X_TIME_H_
#include <string>
#include <sys/types.h>
#include <stdint.h>
#include "x_singleton.h"

class CTime : public SingletonTmpl<CTime>
{
public:
    CTime(int) {}

protected:
    CTime() {}

public:
	std::string GetLocalTime();
	uint64_t GetLocalTime(std::string &strTime);
	std::string GetLocalTimeASC();
	uint64_t GetLocalTime(int) const;
};
#endif //~__X_TIME_H_
