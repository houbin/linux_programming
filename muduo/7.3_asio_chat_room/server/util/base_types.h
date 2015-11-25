#ifndef BASE_TYPE_H_
#define BASE_TYPE_H_

#ifdef _WIN32

#else
#include <sys/types.h>
#include <stdint.h>
#include <errno.h>
#endif

#ifdef _WIN32

#if (MSC_VER >= 1800) //VS 2013+
#include <stdint.h>
#else
typedef char                    int8_t
typedef short                   int16_t
typedef int                     int32_t
typedef long long               int64_t
typedef unsigned char           uint8_t
typedef unsigned short          uint16_t
typedef unsigned int            uint32_t
typedef unsigned long long      uint64_t
#endif

typedef int socklen_t
#else
typedef int BOOL;
const int TRUE = 1;
const int FALSE = 0;

#endif

#endif

