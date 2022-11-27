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

#define ArrayCount(array) (sizeof(array) / sizeof((array)[0]))
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

union v2
{
    struct
    {
        f32 x;
        f32 y;
    };
    f32 e[2];
};
internal v2 V2(f32 x, f32 y)
{
    v2 result = {};
    result.x = x;
    result.y = y;
    return(result);
}

union v3
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
    };
    struct
    {
        f32 r;
        f32 g;
        f32 b;
    };
    struct
    {
        f32 x;
        f32 y;
        f32 _unused0;
    };
    struct
    {
        f32 r;
        f32 g;
        f32 _unused1;
    };
    f32 e[3];
};
internal v3 V3(f32 x, f32 y, f32 z)
{
    v3 result = {};
    result.x = x;
    result.y = y;
    result.z = z;
    return(result);
}

union v4
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    struct 
    {
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };
    f32 e[4];
};

struct m2
{
    f32 e[2][2];
};

struct m3
{
    f32 e[3][3];
};

struct m4
{
    f32 e[4][4];
};


#define TYPES_H
#endif //TYPES_H
