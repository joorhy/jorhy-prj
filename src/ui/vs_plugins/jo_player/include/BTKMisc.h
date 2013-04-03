#pragma once

static inline btk_mtime_t BTK_ntohll(btk_mtime_t &val)
{
	return (((btk_mtime_t)ntohl((int)((val << 32) >> 32))) << 32) |
			(unsigned int)ntohl((int)(val >> 32));
}

static inline btk_mtime_t BTK_htonll(btk_mtime_t &val)
{
	return (((btk_mtime_t)htonl((int)((val << 32) >> 32))) << 32) |	\
			(unsigned int)htonl((int)(val >> 32));
}


