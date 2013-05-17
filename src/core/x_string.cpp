#include "x_string.h"
#include "assert.h"

CXString::CXString()
{
	m_skip_len = 0;
	m_str_len = 0;
}

CXString::CXString(const string_t &str)
{
	m_skip_len = 0;
	m_str = str;
	m_str_len = m_str.length();
}

CXString::~CXString()
{

}

CXString &CXString::operator >> (const CXSkip &s) throw(std::out_of_range)
{
	m_skip_len += s.len;
	if (m_skip_len > m_str_len)
		throw std::out_of_range("CXString &CXString::operator >> skip out_of_range");

	return *this;
}

CXString &CXString::operator >> (CXChar_1 &c) throw(std::out_of_range)
{
	if (m_skip_len + 1 > m_str_len)
		throw std::out_of_range("CXString &CXString::operator >> char_1 out_of_range");
	else
	{
		memcpy(c.data, m_str.data() + m_skip_len, 1);
		m_skip_len += 1;
	}
	return *this;
}

CXString &CXString::operator >> (CXChar_2 &c) throw(std::out_of_range)
{
	if (m_skip_len + 2 > m_str_len)
		throw std::out_of_range("CXString &CXString::operator >> char_2 out_of_range");
	else
	{
		memcpy(c.data, m_str.data() + m_skip_len, 2);
		m_skip_len += 2;
	}
	return *this;
}

CXString &CXString::operator >> (CXChar_3 &c) throw(std::out_of_range)
{
	if (m_skip_len + 3 > m_str_len)
			throw std::out_of_range("CXString &CXString::operator >> char_3 out_of_range");
	else
	{
		memcpy(c.data, m_str.data() + m_skip_len, 3);
		m_skip_len += 3;
	}
	return *this;
}

CXString &CXString::operator >> (CXChar_5 &c) throw(std::out_of_range)
{
	if (m_skip_len + 5 > m_str_len)
			throw std::out_of_range("CXString &CXString::operator >> char_5 out_of_range");
	else
	{
		memcpy(c.data, m_str.data() + m_skip_len, 5);
		m_skip_len += 5;
	}
	return *this;
}

CXString &CXString::operator >> (CXFloat &f) throw(std::out_of_range)
{
	if (m_skip_len + 5 > m_str_len)
			throw std::out_of_range("CXString &CXString::operator >> float out_of_range");
	else
	{
		char data[6] = {0};
		memcpy(data, m_str.data() + m_skip_len, 5);
		m_skip_len += 5;

		bool flag = true;
		if (data[0] == '1')
			flag = false;
		memmove(data, data + 1, 4);
		if (!flag)
			f.u_data.f_data = -atof(data) * 1.0;
		else
			f.u_data.f_data = atof(data) * 1.0;
	}

	return *this;
}

CXString &CXString::operator >> (CXTillFirst &str) throw(std::out_of_range)
{
	if (m_skip_len > m_str_len)
			throw std::out_of_range("CXString &CXString::operator >> char_1 out_of_range");
	else
	{
		string_t cur_str = m_str.substr(m_skip_len, m_str.length() - m_skip_len);
		int index = cur_str.find(str.tag);
		if (index > 0)
		{
			str.str = cur_str.substr(0, index);
			m_skip_len += index;
		}
	}
	return *this;
}

CXString &CXString::operator << (const CXChar_1 &c)
{
	m_str.append(c.data);

	return *this;
}

CXString &CXString::operator << (const CXChar_2 &c)
{
	m_str.append(c.data);

	return *this;
}

CXString &CXString::operator << (const CXChar_3 &c)
{
	m_str.append(c.data);

	return *this;
}

CXString &CXString::operator << (const CXChar_4 &c)
{
	m_str.append(c.data);

	return *this;
}

CXString &CXString::operator << (const CXChar_5 &c)
{
	m_str.append(c.data);

	return *this;
}

CXString &CXString::operator << (const CXFloat &f)
{
	m_str.append(f.u_data.c_data);

	return *this;
}

CXString &CXString::operator << (const char *str)
{
	m_str.append(str);

	return *this;
}

string_t CXString::toString()
{
	return m_str;
}

CXString &CXString::operator >> (CXChar_n &c) throw(std::out_of_range)
{
	char *p = (char *)m_str.c_str();
	char *p2 = strstr(p, c.key);
	if (p2 != NULL)
	{
		p = p2 + strlen(c.key);
		p2 = strstr(p, c.end);
		if (p2 != NULL)
		{
			assert((unsigned int)(p2 - p) < sizeof(c.data));
			memcpy(c.data, p, p2 - p);
		}
		else
		{
			p2 = strstr(p, " ");
			if (p2 != NULL)
			{
				assert((unsigned int)(p2 - p) < sizeof(c.data));
				memcpy(c.data, p, p2 - p);
			}
		}
	}
	return *this;
}

CXString &CXString::operator >> (CXInteger32 &c) throw(std::out_of_range)
{
	char *p = (char *)m_str.c_str();
	char *p2 = strstr(p, c.key);
	if (p2 != NULL)
	{
		p = p2 + strlen(c.key);
		p2 = strstr(p, c.end);
		if (p2 != NULL)
		{
			assert((unsigned int)(p2 - p) < sizeof(c.u_data.c_data));
			memcpy(c.u_data.c_data, p, p2 - p);
			c.u_data.i_data = atoi(c.u_data.c_data);
		}
		else
		{
			p2 = strstr(p, " ");
			if (p2 != NULL)
			{
				assert((unsigned int)(p2 - p) < sizeof(c.u_data.c_data));
				memcpy(c.u_data.c_data, p, p2 - p);
				c.u_data.i_data = atoi(c.u_data.c_data);
			}
		}
	}
	return *this;
}

CXString &CXString::operator >> (CXInteger64U &c) throw(std::out_of_range)
{
	char *p = (char *)m_str.c_str();
	char *p2 = strstr(p, c.key);
	if (p2 != NULL)
	{
		p = p2 + strlen(c.key);
		p2 = strstr(p, c.end);
		if (p2 != NULL)
		{
			assert((unsigned int)(p2 - p) < sizeof(c.u_data.c_data));
			memcpy(c.u_data.c_data, p, p2 - p);
#ifdef WIN32
			c.u_data.i_data = _atoi64(c.u_data.c_data);
#else
			c.u_data.i_data = atoll(c.u_data.c_data);
#endif
		}
		else
		{
			p2 = strstr(p, " ");
			if (p2 != NULL)
			{
				assert((unsigned int)(p2 - p) < sizeof(c.u_data.c_data));
				memcpy(c.u_data.c_data, p, p2 - p);
#ifdef WIN32
				c.u_data.i_data = _atoi64(c.u_data.c_data);
#else
				c.u_data.i_data = atoll(c.u_data.c_data);
#endif
			}
		}
	}
	return *this;
}

CXString &CXString::operator >> (CXFloat2 &c) throw(std::out_of_range)
{
	char *p = (char *)m_str.c_str();
	char *p2 = strstr(p, c.key);
	if (p2 != NULL)
	{
		p = p2 + strlen(c.key);
		p2 = strstr(p, c.end);
		if (p2 != NULL)
		{
			assert((unsigned int)(p2 - p) < sizeof(c.u_data.c_data));
			memcpy(c.u_data.c_data, p, p2 - p);
			c.u_data.f_data = atof(c.u_data.c_data);
		}
		else
		{
			p2 = strstr(p, " ");
			if (p2 != NULL)
			{
				assert((unsigned int)(p2 - p) < sizeof(c.u_data.c_data));
				memcpy(c.u_data.c_data, p, p2 - p);
				c.u_data.f_data = atof(c.u_data.c_data);
			}
		}
	}
	return *this;
}

