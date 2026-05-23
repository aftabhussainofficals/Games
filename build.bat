@echo off
cd /d "%~dp0"

echo Building Tetris engine...
pushd "%~dp0tetris"
call build.bat
popd

echo.
echo Building Game Hub...
g++ Menu.cpp -I . -o Games.exe
if %errorlevel% equ 0 (
    echo.
    echo Build successful! Run GameHub.exe to start.
) else (
    echo Build failed!
    pause
)
