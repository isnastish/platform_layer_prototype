#include "string_guard.h"

#if _WIN32
#include "win32.h"
#endif

internal void Printf(char *format, ...)
{
    char buf[4096];
    
#if 0
    // %v2 %V2 -> 2 component vector
    // %v3 %V3 -> 3 component vector
    // %v4 %V4 -> 4 component vector
    // %m4 %M4 -> 4x4 
    // %m3 %M3 -> 3x3
    // %m2 %M2 -> 2x2
    
    for(;;)
    {
        char c = AdvanceChars(&format, 1); // return *format before advancing it
        if(c == '%')
        {
            if(OneOf("vV", c))
            {
                switch(*format)
                {
                    case '2':
                    {
                    }break;
                    case '3':
                    {
                    }break;
                    case '4':
                    {
                    }break;
                    default:
                    {
                        // TODO(al): An error, unknown format specifier!!!
                        InvalidCodePath();
                    }break;
                }
            }
            else if(OneOf("mM", c))
            {
                switch(*format)
                {
                    case '2':
                    {
                    }break;
                    case '3':
                    {
                    }break;
                    case '4':
                    {
                    }break;
                    default:
                    {
                        // TODO(al): An error, unknown format specifier!!!
                        InvalidCodePath();
                    }break;
                }
            }
            else if(OneOf("iI", c))
            {
            }
            else if(OneOf("uU", c))
            {
            }
            else if(OneOf("fF", c))
            {
            }
            else if(OneOf("sS", c))
            {
            }
            else if(OneOf("cC", c))
            {
            }
        }
        else
        {
            // NOTE(al): Just add the string to the buffer.
        }
    }
#endif
}

internal void Printf_s(string *format, ...)
{
}