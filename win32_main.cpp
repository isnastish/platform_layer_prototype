#include "os.h"
#include "timer.h"
#include "win32.h"

struct W32AppCode
{
    HMODULE                   dll;
    app_update_and_render_ptr update_and_render;
    b32                       result;
};

internal void W32LoadAppCode(W32AppCode *app_code, char *dll_name)
{
    app_code->dll = LoadLibraryA(dll_name);
    if(app_code->dll)
    {
        app_code->update_and_render = (app_update_and_render_ptr)GetProcAddress(app_code->dll, "app_update_and_render");
        if(!app_code->update_and_render)
        {
            app_code->update_and_render = app_update_and_render_stub;
        }
        else
        {
            app_code->result = 1;
        }
    }
    else
    {
        // TODO(al): Not really an error but our application won't be able to update and render things
    }
}

// Let's pass the name as a char *, and will try to figure out how to put it in the struct later.
// The only problem with this approach is that we don't know whether we loaded the dll fo the first time.
// But, for now, let's assume that the DLL was loaded correctly.
internal void W32UnloadAppCode(W32AppCode *app_code)
{
    Assert(FreeLibrary(app_code->dll) != 0);
}

internal s64 W32QueryPerformanceFrequency()
{
    u64 result;
    QueryPerformanceFrequency((LARGE_INTEGER *)&result);
    return(result);
}

internal s64 W32QueryPerformanceCounter()
{
    u64 result;
    QueryPerformanceCounter((LARGE_INTEGER *)&result);
    return(result);
}

internal u64 W32Rdtsc()
{
    u64 result = __rdtsc();
    return(result);
}

inline internal void W32Sleep(u32 ms)
{
    // NOTE(al): We have to make sure that we will be able to sleep the amount of time we specified.
    Sleep((DWORD)ms);
}

internal Thread W32CreateThread(void *thread_proc, void *param, u32 flags)
{
    // NOTE(al): Do I need to assert thread's id here?
    Thread result;
    result.handle = (u64)CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread_proc, param, flags, (LPDWORD)&result.id);
    Assert(result.handle);
    return(result);
}

s32 W32LockedIncrement(volatile s32 *addend)
{
    s32 result = (s32)InterlockedIncrement((volatile LONG *)addend);
    return(result);
}

s64 W32LockedIncrement64(volatile s64 *addend)
{
    s64 result = (s64)InterlockedIncrement64((volatile LONG64 *)addend);
    return(result);
}

s32 W32LockedExchangeAdd(volatile s32 *addend, s32 value)
{
    s32 result = (s32)InterlockedExchangeAdd((volatile LONG *)addend, (LONG)value);
    return(result);
}

s64 W32LockedExchangeAdd64(volatile s64 *addend, s64 value)
{
    s64 result = (s64)InterlockedExchangeAdd64((volatile LONG64 *)addend, (LONG64)value);
    return(result);
}

s32 W32LockedExchange(volatile s32 *target, s32 value)
{
    s32 result = (s32)InterlockedExchange((volatile LONG *)target, (LONG)value);
    return(result);
}

s64 W32LockedExchange64(volatile s64 *target, s64 value)
{
    s64 result = (s64)InterlockedExchange64((volatile LONG64 *)target, (LONG64)value);
    return(result);
}

void *W32LockedExchangePtr(volatile void **target, void *value)
{
    void *result = InterlockedExchangePointer((volatile PVOID *)target, (PVOID)value);
    return(result);
}

s32 W32LockedCompareExchange(volatile s32 *destination, s32 exchange, s32 comperand)
{
    s32 result = (s32)InterlockedCompareExchange((volatile LONG *)destination, (LONG)exchange, (LONG)comperand);
    return(result);
}

s64 W32LockedCompareExchange64(volatile s64 *destination, s64 exchange, s64 comperand)
{
    s64 result = (s64)InterlockedCompareExchange64((volatile LONG64 *)destination, (LONG64)exchange, (LONG64)comperand);
    return(result);
}

void *W32LockedCompareExchangePtr(volatile void **destination, void *exchange, void *comperand)
{
    void *result = InterlockedCompareExchangePointer((volatile PVOID *)destination, (PVOID)exchange, (PVOID)comperand);
    return(result);
}

INT WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR cmd_line, int show_code)
{
    OsState os_state = {};
    // time
    os_state.timer_get_frequency = W32QueryPerformanceFrequency;
    os_state.timer_get_rdtsc     = W32Rdtsc;
    os_state.timer_get_qpc       = W32QueryPerformanceCounter;
    os_state.timer_sleep         = W32Sleep;
    
    // threads
    os_state.create_thread               = W32CreateThread;
    os_state.locked_increment            = W32LockedIncrement;
    os_state.locked_increment64          = W32LockedIncrement64;
    os_state.locked_exchange_add         = W32LockedExchangeAdd;
    os_state.locked_exchange_add64       = W32LockedExchangeAdd64;
    os_state.locked_exchange             = W32LockedExchange;
    os_state.locked_exchange64           = W32LockedExchange64;
    os_state.locked_exchange_ptr         = W32LockedExchangePtr;
    os_state.locked_compare_exchange     = W32LockedCompareExchange;
    os_state.locked_compare_exchange64   = W32LockedCompareExchange64;
    os_state.locked_compare_exchange_ptr = W32LockedCompareExchangePtr;
    
    global_os_state = os_state;
    
    W32AppCode app_code = {};
    W32LoadAppCode(&app_code, "e:/work/build/app_code.dll");
    if(app_code.result)
    {
        app_code.update_and_render(&global_os_state);
    }
    
    ExitProcess(0);
}