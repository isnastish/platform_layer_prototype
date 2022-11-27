#ifndef STRING_GUARD_H
#include <string.h>
#include <malloc.h>
#include "types.h"
#include "arena.h"

// NOTE(al): To make it more generic, we can name the struct "buffer" and introduce the typedef.
// typedef buffer string;
struct string
{
    u32 count;
    u32 memory_size;
    char *data;
};

internal string String(Arena *arena, char *start, char *end)
{
    string result = {};
    
    u32 chars_count = (end - start);
    size_t alloc_size = (chars_count < 512u) ? 512u : chars_count;
    
    // TODO(al): e:\work\win32_threads\code\win32_main.cpp(169): error C2129: static function 'void *arena_alloc(Arena *,u64,u64)' declared but not defined
    //e:\work\win32_threads\code\arena.h(13): note: see declaration of 'arena_alloc'
    
    
    //result.data = (char *)arena_alloc(arena, alloc_size, sizeof(u32));
    result.count = chars_count;
    result.memory_size = alloc_size;
    
    // TODO(al): Replace with StrnCopy!!!
    strncpy(result.data, start, result.count);
    
    return(result);
}

// NOTE(al): Don't want to hardcode it to 32.
#define aA ('a' - 'A')
#define const

internal char AdvanceChars(char **at, u32 n)
{
    // TODO(al): We have to introduce a notion of how to determine that 
    // we advanced exactly the amount we specified (n)!!!
    char c = **at;
    for(s32 count = 0; 
        (**at != 0) && (count < n); 
        ++count)
    {
        *at++;
    }
    return(c);
}

// TODO(al): Not implemented yet!!!
internal void *MemSet(void *dest, char c, u32 count);
internal void *MemCopy(void *dest, const void *source, u32 count);

#define IsUpperMacro(c) (b32)(((c) >= 'A') && ((c) <= 'Z'))
#define IsLowerMacro(c) (b32)(((c) >= 'a') && ((c) <= 'z'))
#define ToLowerMacro(c) (b32)(IsUpperMacro(c) ? ((c) + aA) : (c))
#define ToUpperMacro(c) (b32)(IsLowerMacro(c) ? ((c) - aA) : (c))
#define IsDigitMacro(c) (b32)(((c) >= '0') && ((c) <= '9'))
#define IsAlphaMacro(c) (b32)(IsLowerMacro(c) || IsUpperMacro(c))
#define IsAlnumMacro(c) (b32)(IsDigitMacro(c) || IsAlphaMacro(c))
#define OneOfMacro(s, c) (b32)((s[0] == c) || (s[1] == c))
#define IsWhiteMacro() ((c == ' ') || \
(c == '\n') ||\
(c == '\r') ||\
(c == '\t') ||\
(c == '\v') ||\
(c == '\f'))
#define IsNewLineMacro() (b32)((c == '\n') || (c == '\r'))
#define W32IsNewLineMacro(s) (b32)(((s[0] == '\n') && (s[1] == '\r')) ||\
((s[0] == '\r') && (s[1] == '\n')))
inline internal b32 IsUpper(char c)
{
    b32 result = ((c >= 'A') && (c <= 'Z'));
    return(result);
}

inline internal b32 IsLower(char c)
{
    b32 result = ((c >= 'a') && (c <= 'z'));
    return(result);
}

inline internal char ToLower(char c)
{
    char result = IsUpper(c) ? (c + aA) : c;
    return(result);
}

inline internal char ToUpper(char c)
{
    char result = IsLower(c) ? (c - aA) : c;
    return(result);
}

inline internal b32 IsDigit(char c)
{
    b32 result = ((c >= '0') && (c <= '9'));
    return(0);
}

inline internal b32 IsAlpha(char c) 
{
    b32 result = (((c >= 'a') && (c <= 'z')) ||
                  ((c >= 'A') && (c <= 'Z')));
    return(0);
}

inline internal b32 IsAlnum(char c)
{
    b32 result = IsDigit(c) || IsAlpha(c);
    return(result);
}

inline internal b32 OneOf(const char *s, char c)
{
    b32 result = ((s[0] == c) || (s[1] == c));
    return(result);
}

inline internal b32 IsWhite(char c)
{
    b32 result = ((c == ' ') ||
                  (c == '\n') ||
                  (c == '\r') ||
                  (c == '\t') ||
                  (c == '\v') ||
                  (c == '\f'));
    return(result);
}

inline internal b32 IsNewLine(char c)
{
    b32 result = ((c == '\n') || (c == '\r'));
    return(result);
}

inline internal b32 W32IsNewLine(const char *s)
{
    b32 result = (((s[0] == '\n') && (s[1] == '\r')) ||
                  ((s[0] == '\r') && (s[1] == '\n')));
    return(result);
}

internal u32 StrLen(const char *s)
{
    u32 result = 0;
    while(*s++)
    {
        ++result;
    }
    return(result);
}

internal s32 StrComp(const char *s0, const char *s1)
{
    s32 result = 0;
    for(; *s0 == *s1; s0++, s1++)
    {
        if(*s0 == 0)
        {
            return(result);
        }
    }
    result = *s0 - *s1;
    return(result);
}

internal s32 StrnComp(const char *s0, const char *s1, u32 n)
{
    s32 result = 0;
    for(s32 count = 0;
        (*s0 == *s1) && (count < n);
        s0++, s1++, count++)
    {
        if((*s0 == 0) && (count == (n - 1)))
        {
            return(result);
        }
    }
    result = *s0 - *s1;
    return(result);
}

internal char *StrCopy(char *dest, const char *source)
{
    char *result = dest;
    while((*dest++ = *source++) != 0)
    {
        ;
    }
    return(result);
}

internal char *StrnCopy(char *dest, u32 dest_size, const char *source)
{
    char *result = 0;
    for(u32 copied_count = 0;
        copied_count != dest_size;
        ++copied_count)
    {
        *dest++ = *source++;
    }
    return(result);
}


// TODO(al): Implement case-insensitive StrComp function
internal s32 StrCompI(const char *s0, const char *s1)
{
    s32 result = 0;
    return(result);
}

#undef const
#define STRING_GUARD_H
#endif //STRING_GUARD_H
