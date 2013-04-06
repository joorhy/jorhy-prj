#pragma once

template <typename CBase>
class SingletonTmpl
{
public:
	static CBase *Instance()
	{
		if (0 == m_instance)
			m_instance = new CBase();

		return m_instance;
	}

private:
	static CBase *m_instance;
};

template <typename CBase>
CBase * SingletonTmpl<CBase>::m_instance = 0;
