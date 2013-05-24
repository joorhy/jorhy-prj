#ifndef _X_SDK_DEF_H_
#define _X_SDK_DEF_H_
#include "j_includes.h"

//using namespace std;
struct _cha
{
	j_int32_t cha;	
	j_string_t resid;
	j_int32_t ms;
};

struct _res	
{
	j_int32_t id;
	j_int32_t type;
	j_string_t ip;
	j_int32_t port;
	j_string_t user;
	j_string_t pass;	
	std::vector<_cha> chanum;
};

struct _parm
{
	j_string_t store;	
	j_int32_t segment_h;
	j_int32_t segment_a;
	std::vector<_res> resnum;	
};

struct r_register
{
	j_int32_t cmd;	
	j_int32_t rst;
	_parm parm;	
};

struct r_devconfig
{
	j_int32_t rst;
	struct
	{
		j_int32_t id;
		j_string_t type;		
		j_string_t ip;		
		j_int32_t 	port;		
		j_string_t user;	
		j_string_t pass;		
		j_int32_t 	cha;		
		j_string_t resid;		
		j_int32_t 	ms;			
		j_int32_t	store;	
	}parm;
};

struct r_ssconfig
{
	j_int32_t rst;	
	struct
	{
		j_string_t ip;	
		j_int32_t 	port;	
	}parm;
};

struct r_historyfile
{
	j_int32_t rst;
	struct
	{
		j_int32_t dvr;
		std::vector<j_string_t> files;
	}parm;
};

struct s_fileinfo
{
	j_string_t file;
	time_t		stime;
	time_t		etime;
};
struct s_record
{
	j_string_t resid;
	std::vector<s_fileinfo> filenum;
};

struct r_recordcol
{
	j_int32_t act;		
	j_string_t resid;
	j_int32_t ms;	
};

/*cmd=102*/
struct r_DVRrecord
{
	j_string_t resid;
	time_t stime;
	time_t etime;
};

/*cmd=103*/
struct r_cameracol
{
	j_string_t resid;
	j_int32_t action;
	j_int32_t value;	
};

/*cmd=104*/
struct r_filemove
{
	j_string_t resid;
	j_int32_t type;
	j_string_t files;
	time_t stime;
	time_t etime;
	j_string_t dist;	
};

/*cmd=105*/
struct r_rcd_search
{
	j_string_t resid;
	time_t begin_time;
	time_t end_time;				
};

#endif //~_X_SDK_DEF_H_
