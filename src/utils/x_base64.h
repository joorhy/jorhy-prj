#ifndef __X_BASE64_H_
#define __X_BASE64_H_

#ifdef WIN32

#ifdef UTILS_LIB_EXPORTS
#define BASE64_DLLAPI	_declspec(dllexport)
#else
#define BASE64_DLLAPI	_declspec(dllimport)
#endif

#else
#define BASE64_DLLAPI
#endif

void BASE64_DLLAPI base64_in (unsigned char *buf, char *obuf, int len);
void BASE64_DLLAPI base64_out (char *buf, unsigned char *obuf, int len);

#endif //~__X_BASE64_H_
