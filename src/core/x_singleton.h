#ifndef __SINGLETON_H_
#define __SINGLETON_H_

template <typename CBase>
class SingletonTmpl
{
public:
	static CBase *Instance()
	{
		if (0 == m_instance)
			m_instance = new CBase(0);

		return m_instance;
	}

private:
	static CBase *m_instance;
};

template <typename CBase>
CBase * SingletonTmpl<CBase>::m_instance = 0;

#endif //~__SINGLETON_H_
