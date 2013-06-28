#ifndef __X_STRING_H_
#define __X_STRING_H_
#include "j_common.h"

/***************************************用****法****示****例***********************************************
 	#include "Utility/include/x_string.h"

  	CXString test_out("BEGIN1008ff037humidityburst:034.2,100.5,045.6,005.2");
	CXChar_5 char_5;
	CXChar_1 char_1;
	CXChar_3 char_3;
	CXFloat temp;
	CXFloat temp2;
	CXTillFirst till(":");
	test_out >> char_5 >> char_1 >> char_3 >> 5 >> till >> 1 >> temp >> 1 >> temp2;

	CXString test_in;
	test_in << "BEGIN" << CXChar_1().FillBuff("1") << CXChar_3().FillBuff("8");
	test_in << "ff" << "037" << "humidityburst";
	test_in	<< ":" << 34.2 << "," << -0.5  << "," << 45.6 << "," << 5.2;
	string_t cmd = test_in.toString();
	cout << cmd << endl;
 ************************************************************************************************************/

#define EPSINON 0.01
typedef std::string string_t;

struct CXSkip
{
	CXSkip(int len_)
	{
		len = len_;
	}
	int len;
};

struct CXChar_1
{
	char data[2];
	CXChar_1()
	{
		memset(data, 0, sizeof(data));
	}

	CXChar_1 &FillBuff(const char *data_)
	{
		memset(data, 0, sizeof(data));
		sprintf(data, "%s", data_);
		return *this;
	}
};

struct CXChar_2
{
	char data[3];
	CXChar_2()
	{
		memset(data, 0, sizeof(data));
	}

	CXChar_2 &FillBuff(const char *data_)
	{
		memset(data, 0, sizeof(data));
		sprintf(data, "%02d", atoi(data_));
		return *this;
	}
};

struct CXChar_3
{
	char data[4];
	CXChar_3()
	{
		memset(data, 0, sizeof(data));
	}

	CXChar_3 &FillBuff(const char *data_)
	{
		memset(data, 0, sizeof(data));
		sprintf(data, "%03d", atoi(data_));
		return *this;
	}
};

struct CXChar_4
{
	char data[5];
	CXChar_4()
	{
		memset(data, 0, sizeof(data));
	}

	CXChar_4 &FillBuff(const char *data_)
	{
		memset(data, 0, sizeof(data));
		sprintf(data, "%04d", atoi(data_));
		return *this;
	}
};

struct CXChar_5
{
	char data[6];
	CXChar_5()
	{
		memset(data, 0, sizeof(data));
	}

	CXChar_5 &FillBuff(const char *data_)
	{
		memset(data, 0, sizeof(data));
		sprintf(data, "%05d", atoi(data_));
		return *this;
	}
};

struct CXChar_n
{
	char key[32];
	char end[32];
	char data[256];
	CXChar_n()
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		memset(data, 0, sizeof(data));
	}
	CXChar_n(const char *p_key, const char *p_end)
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		memcpy(key, p_key, strlen(p_key));
		memcpy(end, p_end, strlen(p_end));
		memset(data, 0, sizeof(data));
	}
	CXChar_n &FillBuff(const char *data_)
	{
		memset(data, 0, sizeof(data));
		sprintf(data, "%s", data_);
		return *this;
	}
	const char *operator()()
	{
		return this->data;
	}
};

struct CXInteger32
{
	char key[32];
	char end[32];
	union
	{
		char c_data[20];
		int i_data;
	} u_data;
	CXInteger32()
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		u_data.i_data = 0;
	}

	CXInteger32(const char *p_key, const char *p_end)
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		memcpy(key, p_key, strlen(p_key));
		memcpy(end, p_end, strlen(p_end));
		u_data.i_data = 0;
	}

	explicit CXInteger32(int data_)
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		memset(u_data.c_data, 0, sizeof(u_data.c_data));
		sprintf(u_data.c_data, "%d", data_);
	}

	const int operator()()
	{
		return this->u_data.i_data;
	}
};

struct CXInteger64U
{
	char key[32];
	char end[32];
	union
	{
		char c_data[30];
		unsigned long long i_data;
	} u_data;
	CXInteger64U()
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		u_data.i_data = 0;
	}

	CXInteger64U(const char *p_key, const char *p_end)
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		memcpy(key, p_key, strlen(p_key));
		memcpy(end, p_end, strlen(p_end));
		u_data.i_data = 0;
	}

	explicit CXInteger64U(long long data_)
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		memset(u_data.c_data, 0, sizeof(u_data.c_data));
		sprintf(u_data.c_data, "%llu", data_);
	}

	const unsigned long long operator()()
	{
		return this->u_data.i_data;
	}
};

struct CXFloat
{
	union
	{
		char c_data[6];
		float f_data;
	} u_data;
	CXFloat()
	{
		u_data.f_data = 0.1;
	}

	explicit CXFloat(float data_)
	{
		memset(u_data.c_data, 0, sizeof(u_data.c_data));
		if (data_ < -EPSINON)
		{
			u_data.c_data[0] = '1';
			sprintf(u_data.c_data + 1, "%04.1f", -data_);
		}
		else
		{
			u_data.c_data[0] = '0';
			sprintf(u_data.c_data + 1, "%04.1f", data_);
		}
	}
};

struct CXFloat2
{
	char key[32];
	char end[32];
	union
	{
		char c_data[30];
		float f_data;
	} u_data;
	CXFloat2()
	{
		u_data.f_data = 0.1;
	}

	CXFloat2(const char *p_key, const char *p_end)
	{
		memset(key, 0, sizeof(key));
		memset(end, 0, sizeof(end));
		memcpy(key, p_key, strlen(p_key));
		memcpy(end, p_end, strlen(p_end));
		u_data.f_data = 0.1;
	}

	explicit CXFloat2(float data_)
	{
		memset(u_data.c_data, 0, sizeof(u_data.c_data));
		if (data_ < -EPSINON)
		{
			u_data.c_data[0] = '1';
			sprintf(u_data.c_data + 1, "%04.1f", -data_);
		}
		else
		{
			u_data.c_data[0] = '0';
			sprintf(u_data.c_data + 1, "%04.1f", data_);
		}
	}

	const float operator()()
	{
		return this->u_data.f_data;
	}
};

struct CXTillFirst
{
	string_t tag;
	string_t str;
	CXTillFirst(const char *tag_)
	{
		tag = tag_;
		str.clear();
	}
};

class JO_API CXString
{
public:
	CXString();
	CXString(const string_t &str);
	~CXString();

public:
	CXString &operator >> (const CXSkip &s) throw(std::out_of_range);
	CXString &operator >> (CXChar_1 &c) throw(std::out_of_range);
	CXString &operator >> (CXChar_2 &c) throw(std::out_of_range);
	CXString &operator >> (CXChar_3 &c) throw(std::out_of_range);
	CXString &operator >> (CXChar_4 &c) throw(std::out_of_range);
	CXString &operator >> (CXChar_5 &c) throw(std::out_of_range);
	CXString &operator >> (CXFloat &f) throw(std::out_of_range);
	CXString &operator >> (CXTillFirst &str) throw(std::out_of_range);

	CXString &operator << (const CXChar_1 &c);
	CXString &operator << (const CXChar_2 &c);
	CXString &operator << (const CXChar_3 &c);
	CXString &operator << (const CXChar_4 &c);
	CXString &operator << (const CXChar_5 &c);
	CXString &operator << (const CXFloat &f);
	CXString &operator << (const char *str);
	string_t toString();

public:
	CXString &operator >> (CXChar_n &c) throw(std::out_of_range);
	CXString &operator >> (CXInteger32 &c) throw(std::out_of_range);
	CXString &operator >> (CXInteger64U &c) throw(std::out_of_range);
	CXString &operator >> (CXFloat2 &f) throw(std::out_of_range);

private:
	string_t m_str;
	int m_skip_len;
	int m_str_len;
};
#endif //~__X_STRING_H_
