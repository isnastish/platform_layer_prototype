#ifndef TIMER_H
#include "os.h"

struct Timer
{
    b32 frequency_cached;
    
    s64 frequency;
    s64 ticks_start;
    s64 cycles_start;
    f64 elapsed_seconds;
    f64 elapsed_milliseconds;
    f64 elapsed_microseconds;
};

internal void timer_push(OsState *os_state, Timer *timer);
internal void timer_pop(OsState *os_state, Timer *timer);

#define TIMER_H
#endif //TIMER_H
