
@echo off

rem NOTE(al): Stack size is set to 4GB.

set CommonCompilerOptions=-nologo -Od -Zi -FC -TP -EHsc -DASSERT_ENABLED -F4294967296 -DINTERNAL_BUILD
set CommonLinkerOptions=user32.lib kernel32.lib

if not exist ..\..\build ( mkdir ..\..\build )
pushd ..\..\build

cl  -Od -Zi ..\win32_threads\code\os.cpp /link /dll /out:app_code.dll
cl %CommonCompilerOptions% ..\win32_threads\code\win32_main.cpp /link %CommonLinkerOptions% /out:threads.exe

popd