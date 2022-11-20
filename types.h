#ifndef TYPES_H
#include <stdio.h>
#include <stdint.h>
#include <intrin.h> // NOTE(al): Not sure whether this is platform-independent header file

//#include <limits.h> // ?
//#include <float.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;
typedef s32 b32;

typedef uintptr_t umm;
typedef intptr_t smm;

#define ArrayCount(array) ((sizeof((array)) / sizeof((array)[0]))
#define OffsetOf(type, member) ((u32)(size_t)(&((type *)0)->member)) // STUDY(al): Do I need to cast it to u32?

#if ASSERT_ENABLED
#define Assert(expr)\
if((expr)){}\
else\
{\
*((u32 *)0u) = 0u;\
}
#else
#define Assert(expr) (void(0))
#endif // ASSERT_ENABLED

#define InvalidCodePath() Assert(0)
#define global static

#if defined(INTERNAL_BUILD)
#define internal static 
#else
#define internal
#endif // INTERNAL_BUILD

#define Terabytes(n) (Gigabytes(n)*(1024ull))
#define Gigabytes(n) (Megabytes(n)*(1024ull))
#define Megabytes(n) (Kilobytes((n))*(1024ull))
#define Kilobytes(n) ((n)*(1024ull))

#define TYPES_H
#endif //TYPES_H
