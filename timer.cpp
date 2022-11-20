#include "timer.h"

internal void timer_push(OsState *os_state, Timer *timer)
{
    if(!timer->frequency_cached)
    {
        timer->frequency = os_state->timer_get_frequency();
        timer->frequency_cached = true;
    }
    timer->cycles_start = os_state->timer_get_rdtsc();
    timer->ticks_start = os_state->timer_get_qpc();
}

internal void timer_pop(OsState *os_state, Timer *timer)
{
    if(timer->frequency_cached)
    {
        s64 cycles_end = os_state->timer_get_rdtsc();
        s64 ticks_end = os_state->timer_get_qpc();
        
        s64 ticks_elapsed = ticks_end - timer->ticks_start;
        s64 cycles_elapsed = cycles_end - timer->cycles_start;
        
        timer->elapsed_seconds = (ticks_elapsed * (1.0 / (f64)timer->frequency));
        timer->elapsed_milliseconds = timer->elapsed_seconds * 1000.0;
        timer->elapsed_microseconds = timer->elapsed_milliseconds * 1000.0;
    }
    else
    {
        // TODO(al): Print an error message.
        InvalidCodePath();
    }
}