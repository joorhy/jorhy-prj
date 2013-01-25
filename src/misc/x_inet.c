#include <stdint.h>

int64_t ntohll(int64_t val)
{
	return (((int64_t)htonl((int32_t)((val << 32) >> 32))) << 32) | (int32_t)htonl((int32_t)(val >> 32));
}

int64_t htonll(int64_t val)

{
	return (((int64_t)htonl((int32_t)((val << 32) >> 32))) << 32) | (int32_t)htonl((int32_t)(val >> 32));
}