#ifndef __SINGLETON_H_
#define __SINGLETON_H_

template <typename CBase>
class SingletonTmpl
{
public:
	static CBase *Instance()
	{
		return &m_instance;
	}

protected:
	typedef CBase object_type; 
	static CBase m_instance;
};

template <typename CBase>
typename SingletonTmpl<CBase>::object_type SingletonTmpl<CBase>::m_instance;

#endif //~__SINGLETON_H_
