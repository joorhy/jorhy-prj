#ifndef __X_CONVERT_H_
#define __X_CONVERT_H_
#include <string>

class BaseConvert
{
public:
	virtual ~BaseConvert() {}
};

template <class T, typename R = void>
class J_Convert
{
public:
	typedef R ReturnType;
	virtual ReturnType Convert(T&) = 0;
};

#endif //~__X_CONVERT_H_
