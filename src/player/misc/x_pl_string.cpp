#include "x_pl_string.h"
#include <string.h>
#include <stdlib.h>

char *J_PlString::StrDup(char *src)
{
	size_t len = strlen (src) + 1;
	char *res = new char[len];
	if(res)
		memcpy (res, src, len);
	return res;
}