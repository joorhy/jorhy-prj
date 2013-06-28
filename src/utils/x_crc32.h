#ifndef __X_CRC32_H_
#define __X_CRC32_H_

#ifdef WIN32

#ifdef UTILS_LIB_EXPORTS
#define CRC_DLLAPI	_declspec(dllexport)
#else
#define CRC_DLLAPI	_declspec(dllimport)
#endif

#else
#define CRC_DLLAPI
#endif

extern CRC_DLLAPI unsigned long get_crc32(const char *buffer, unsigned int size);

#endif //~__X_CRC32_H_
