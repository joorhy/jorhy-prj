#pragma once

static inline j_pl_mtime_t j_pl_ntohll(j_pl_mtime_t &val)
{
	return (((j_pl_mtime_t)ntohl((int)((val << 32) >> 32))) << 32) |
			(unsigned int)ntohl((int)(val >> 32));
}

static inline j_pl_mtime_t j_p_htonll(j_pl_mtime_t &val)
{
	return (((j_pl_mtime_t)htonl((int)((val << 32) >> 32))) << 32) |	\
			(unsigned int)htonl((int)(val >> 32));
}


