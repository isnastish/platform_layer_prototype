#ifndef OS_H
#include <stdarg.h>
#include "types.h"
#include "threads.h"
#include "string_guard.h"

struct OsState
{
    s64 (*timer_get_frequency)();
    s64 (*timer_get_qpc)();
    u64 (*timer_get_rdtsc)();
    void (*timer_sleep)(u32 ms);
    //void (*timer_push)(OsState *os_state, Timer *timer);
    //void (*timer_pop)(OsState *os_state, Timer *timer);
    
    // NOTE(al): Think about whether we need to specify the stack_size for the thread.
    Thread (*create_thread)(void *thread_proc,
                            void *param, 
                            u32 flags);
    
    s32 (*locked_increment)(volatile s32 *addend); // increase by 1 (32 bit signed integer)
    s64 (*locked_increment64)(volatile s64 *addend); // increase by 1 (64 bit signed integer)
    
    s32 (*locked_exchange_add)(volatile s32 *addend, s32 value); // atomic addition of two (32 bit) values
    s64 (*locked_exchange_add64)(volatile s64 *addend, s64 value); // atomic addition of two (64 bit) values
    
    s32 (*locked_exchange)(volatile s32 *target, s32 value); // sets a 32-bit variable to the specified value
    s64 (*locked_exchange64)(volatile s64 *target, s64 value); // set a 64-bit variable to the specified value
    void *(*locked_exchange_ptr)(volatile void **target, void *value); // atomically exchanges a pair of addresses
    
    s32 (*locked_compare_exchange)(volatile s32 *destination, s32 exchange, s32 comperand);
    s64 (*locked_compare_exchange64)(volatile s64 *destination, s64 exchange, s64 comperand);
    void *(*locked_compare_exchange_ptr)(volatile void **destination, void *exchange, void *comperand);
    
    // TODO(al): Not implemented yet. And I don't really know whether we should have a single
    // pointer alloc, which allocate a memory, or we can support commit_memory and reserve_memory.
    void *(*alloc)(u64 size, u64 alignment);
    void *(*commit_memory)(u64 size, u64 alignment);
    void *(*reserve_memory)(u64 size, u64 alignment);
};

#define APP_UPDATE_AND_RENDER(name) void name(OsState *_os_state)
typedef void (*app_update_and_render_ptr)(OsState *os_state);
APP_UPDATE_AND_RENDER(app_update_and_render_stub){}

global OsState global_os_state;

#define OS_H
#endif //OS_H
