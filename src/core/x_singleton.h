#ifndef __SINGLETON_H_
#define __SINGLETON_H_

#ifdef WIN32 
#ifdef JO_SINGLETON_EXPORTS
#define JO_SINGLETON_API __declspec(dllexport)
#else
#define JO_SINGLETON_API __declspec(dllimport)
#endif
#else
#define JO_SINGLETON_API
#endif

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
T *SingletonTmpl<T>::instance = 0;

#endif //~__SINGLETON_H_
