#include <windows.h>

// NOTE(al): It's not a good idea to combine platform-independent and paltform-specific code in one place
// sprintf_s(...) function is platform-independent, but OutputDebugStringA() is not.
// Will have to think about that.
#define Out(s) OutputDebugStringA((s))
#define Out_s(format, ...)\
{\
char buf[4096];\
sprintf_s(buf, sizeof(buf), (format), ## __VA_ARGS__);\
Out(buf);\
}