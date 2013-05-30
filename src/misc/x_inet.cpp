#include "j_common.h"

extern "C"
{
j_int64_t ntohll(j_int64_t val)
{
	return (((j_int64_t)htonl((j_int32_t)((val << 32) >> 32))) << 32) | (j_int32_t)htonl((j_int32_t)(val >> 32));
}

j_int64_t htonll(j_int64_t val)

{
	return (((j_int64_t)htonl((j_int32_t)((val << 32) >> 32))) << 32) | (j_int32_t)htonl((j_int32_t)(val >> 32));
}

}