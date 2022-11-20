#include "types.h"
#include "os.h"
#include "timer.cpp"

#if _WIN32
#include "win32.h"
#endif

extern "C" __declspec(dllexport) 
APP_UPDATE_AND_RENDER(app_update_and_render)
{
#if _WIN32
    Out("Hello from App Code\n");
#endif
}


#if _WIN32
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    switch(reason) 
    {
        case DLL_PROCESS_ATTACH:
        {
            // Initialize once for each new process.
            // Return FALSE to fail DLL load.s
            Out_s("DLL_PROCESS_ATTACH: %i\n", DLL_PROCESS_ATTACH);
        }break;
        case DLL_THREAD_ATTACH:
        {
            // Do thread-specific initialization.
            Out_s("DLL_THREAD_ATTACH: %i\n", DLL_THREAD_ATTACH);
        }break;
        case DLL_THREAD_DETACH:
        {
            // Do thread-specific cleanup.
            Out_s("DLL_THREAD_DETACH: %i\n", DLL_THREAD_DETACH);
        }break;
        case DLL_PROCESS_DETACH:
        {
            // Perform any necessary cleanup.
            Out_s("DLL_PROCESS_DETACH: %i\n", DLL_PROCESS_DETACH);
        }break;
    }
    return(TRUE);
}
#endif