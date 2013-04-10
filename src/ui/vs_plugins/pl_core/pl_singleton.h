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

	static void Destroy()
	{
		if (0 != m_instance)
		{
			delete m_instance;
			m_instance = 0;
		}
	}

private:
	static CBase *m_instance;
};

template <typename CBase>
CBase * SingletonTmpl<CBase>::m_instance = 0;
