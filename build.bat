@echo off
echo Compiling Games Launcher...
g++ -o launcher.exe main.cpp
if %errorlevel% == 0 (
    echo Build successful! Run launcher.exe to start.
) else (
    echo Build failed.
)
pause
