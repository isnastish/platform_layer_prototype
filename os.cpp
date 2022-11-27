#include "types.h"
#include "os.h"
#include "timer.cpp"
#include "threads.cpp"
#include "arena.cpp"
#include "printf.cpp"

#if _WIN32
#include "win32.h"
#define EXTERN extern "C" __declspec(dllexport)
#else
#define EXTERN extern "C"
#endif

EXTERN APP_UPDATE_AND_RENDER(app_update_and_render)
{
    OsState *os_state = _os_state;
    
    {
        Arena arena = arena_init(Kilobytes(4));
        v3 camera_d = V3(0, 0, 1);
        v3 camera_p = V3(0, -1, 0);
        char *fmt = "CameraDirection: %v3\nCameraPosition: %v3\n\n";
        
        Printf(fmt, camera_d, camera_p);
        
        string format = String(&arena, fmt, (fmt + StrLen(fmt)));
        Printf_s(&format, camera_d, camera_p);
    }
}
