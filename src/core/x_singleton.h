#ifndef __SINGLETON_H_
#define __SINGLETON_H_

#include "j_common.h"

template <typename T>
class SingletonTmpl
{
private:
	static T *instance;  
public:
	static T *Instance()
	{
		if (instance == 0)
		{
			instance = new T();
		}

		return instance; 
	}
};

template<class T>
T *SingletonTmpl<T>::instance = SingletonTmpl<T>::Instance();

#endif //~__SINGLETON_H_
