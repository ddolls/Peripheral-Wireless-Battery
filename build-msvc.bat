@echo off
setlocal enabledelayedexpansion
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" || exit /b 1
cd /d "%~dp0"

powershell -ExecutionPolicy Bypass -File scripts\prep-build.ps1 || exit /b 1

rc /nologo /fo build\app.res /i res /i build res\app.rc || exit /b 1

set CL_FLAGS=/nologo /utf-8 /std:c++17 /O2 /EHsc /DNOMINMAX /D_CRT_SECURE_NO_WARNINGS /DUNICODE /D_UNICODE /MT /W3 /Isrc /Isrc\drivers /Ibuild
set LIBS=user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib hid.lib setupapi.lib cfgmgr32.lib ws2_32.lib winhttp.lib bcrypt.lib version.lib bthprops.lib BluetoothAPIs.lib runtimeobject.lib shlwapi.lib

echo Compiling source files...
cl %CL_FLAGS% /c src\*.cpp src\drivers\*.cpp /Fo:build\ || exit /b 1

echo Linking Peripheral-Wireless-Battery.exe...
link /nologo /SUBSYSTEM:WINDOWS /ENTRY:wWinMainCRTStartup build\*.obj build\app.res %LIBS% /OUT:Peripheral-Wireless-Battery.exe || exit /b 1

echo SUCCESS: Peripheral-Wireless-Battery.exe built successfully!
