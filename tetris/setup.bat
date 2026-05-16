@echo off
SETLOCAL EnableDelayedExpansion
COLOR 0A
TITLE Tetris Game - Automatic Setup

echo.
echo ========================================
echo    TETRIS GAME - AUTOMATIC SETUP
echo ========================================
echo.
echo This script will automatically:
echo  1. Check for existing MinGW installation
echo  2. Download MinGW if not found
echo  3. Install MinGW compiler
echo  4. Configure system PATH
echo  5. Verify installation
echo.
echo Press any key to continue or Ctrl+C to cancel...
pause >nul

:: Check if running as administrator
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo.
    echo [WARNING] This script requires Administrator privileges!
    echo Please right-click setup.bat and select "Run as administrator"
    echo.
    pause
    exit /b 1
)

echo.
echo [STEP 1/5] Checking for existing MinGW installation...
echo ========================================

:: Check common MinGW installation paths
set "MINGW_FOUND=0"
set "MINGW_PATH="

if exist "C:\mingw64\bin\g++.exe" (
    set "MINGW_FOUND=1"
    set "MINGW_PATH=C:\mingw64\bin"
    echo [OK] Found MinGW at C:\mingw64\bin
)

if exist "C:\MinGW\bin\g++.exe" (
    set "MINGW_FOUND=1"
    set "MINGW_PATH=C:\MinGW\bin"
    echo [OK] Found MinGW at C:\MinGW\bin
)

if exist "C:\msys64\mingw64\bin\g++.exe" (
    set "MINGW_FOUND=1"
    set "MINGW_PATH=C:\msys64\mingw64\bin"
    echo [OK] Found MinGW at C:\msys64\mingw64\bin
)

:: Check if g++ is in PATH
where g++ >nul 2>&1
if %errorLevel% equ 0 (
    set "MINGW_FOUND=1"
    echo [OK] g++ compiler found in system PATH
    for /f "tokens=*" %%i in ('where g++') do set "MINGW_PATH=%%~dpi"
)

if !MINGW_FOUND! equ 1 (
    echo.
    echo MinGW is already installed!
    echo Location: !MINGW_PATH!
    echo.
    choice /C YN /M "Do you want to reinstall MinGW"
    if errorlevel 2 goto :verify_installation
    if errorlevel 1 goto :download_mingw
) else (
    echo [INFO] MinGW not found. Will download and install.
)

:download_mingw
echo.
echo [STEP 2/5] Downloading MinGW...
echo ========================================

:: Create temp directory
set "TEMP_DIR=%TEMP%\tetris_setup"
if not exist "!TEMP_DIR!" mkdir "!TEMP_DIR!"

:: Download MinGW using PowerShell
echo Downloading MinGW-w64 (this may take a few minutes)...
echo Please wait...

powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; $ProgressPreference = 'SilentlyContinue'; Invoke-WebRequest -Uri 'https://github.com/niXman/mingw-builds-binaries/releases/download/13.2.0-rt_v11-rev0/x86_64-13.2.0-release-posix-seh-msvcrt-rt_v11-rev0.7z' -OutFile '!TEMP_DIR!\mingw.7z'}"

if not exist "!TEMP_DIR!\mingw.7z" (
    echo.
    echo [ERROR] Failed to download MinGW!
    echo Please check your internet connection and try again.
    echo.
    echo Alternative: Download manually from:
    echo https://github.com/niXman/mingw-builds-binaries/releases
    echo.
    pause
    exit /b 1
)

echo [OK] Download completed!

echo.
echo [STEP 3/5] Installing MinGW...
echo ========================================

:: Check if 7-Zip is available
where 7z >nul 2>&1
if %errorLevel% equ 0 (
    echo Using 7-Zip to extract...
    7z x "!TEMP_DIR!\mingw.7z" -o"C:\" -y >nul
    goto :extraction_done
)

:: Try to extract using PowerShell (Windows 10+)
echo Extracting MinGW (this may take a few minutes)...
powershell -Command "& {Add-Type -AssemblyName System.IO.Compression.FileSystem; try { [System.IO.Compression.ZipFile]::ExtractToDirectory('!TEMP_DIR!\mingw.7z', 'C:\') } catch { Write-Host 'PowerShell extraction failed, trying alternative method...'; exit 1 }}"

if %errorLevel% neq 0 (
    echo.
    echo [WARNING] Automatic extraction failed!
    echo.
    echo Please extract the file manually:
    echo 1. Download 7-Zip from: https://www.7-zip.org/
    echo 2. Extract !TEMP_DIR!\mingw.7z to C:\
    echo 3. Run this setup script again
    echo.
    pause
    exit /b 1
)

:extraction_done
:: Rename to standard path if needed
if exist "C:\mingw64" (
    echo [OK] MinGW installed to C:\mingw64
    set "MINGW_PATH=C:\mingw64\bin"
) else if exist "C:\x86_64-13.2.0-release-posix-seh-msvcrt-rt_v11-rev0\mingw64" (
    echo Renaming installation directory...
    move "C:\x86_64-13.2.0-release-posix-seh-msvcrt-rt_v11-rev0\mingw64" "C:\mingw64" >nul
    rmdir "C:\x86_64-13.2.0-release-posix-seh-msvcrt-rt_v11-rev0" >nul 2>&1
    echo [OK] MinGW installed to C:\mingw64
    set "MINGW_PATH=C:\mingw64\bin"
) else (
    echo [ERROR] Installation directory not found!
    pause
    exit /b 1
)

echo.
echo [STEP 4/5] Configuring System PATH...
echo ========================================

:: Check if already in PATH
echo !PATH! | find /i "!MINGW_PATH!" >nul
if %errorLevel% equ 0 (
    echo [OK] MinGW is already in system PATH
    goto :verify_installation
)

:: Add to system PATH
echo Adding !MINGW_PATH! to system PATH...
setx PATH "!MINGW_PATH!;%PATH%" /M >nul 2>&1

if %errorLevel% equ 0 (
    echo [OK] PATH updated successfully!
    echo.
    echo [IMPORTANT] Changes will take effect in new command prompt windows.
) else (
    echo [WARNING] Could not update PATH automatically.
    echo Please add manually: !MINGW_PATH!
)

:: Update current session PATH
set "PATH=!MINGW_PATH!;%PATH%"

:verify_installation
echo.
echo [STEP 5/5] Verifying Installation...
echo ========================================

:: Verify g++ is accessible
where g++ >nul 2>&1
if %errorLevel% neq 0 (
    echo [ERROR] g++ compiler not found in PATH!
    echo Please restart your computer and try again.
    pause
    exit /b 1
)

:: Get g++ version
echo Checking g++ version...
g++ --version | findstr "g++"
if %errorLevel% equ 0 (
    echo.
    echo [OK] g++ compiler is working correctly!
) else (
    echo [WARNING] Could not verify g++ version
)

:: Test compilation
echo.
echo Testing compilation...
echo #include ^<iostream^> > "!TEMP_DIR!\test.cpp"
echo int main() { std::cout ^<^< "OK"; return 0; } >> "!TEMP_DIR!\test.cpp"

g++ "!TEMP_DIR!\test.cpp" -o "!TEMP_DIR!\test.exe" 2>nul
if exist "!TEMP_DIR!\test.exe" (
    echo [OK] Test compilation successful!
    del "!TEMP_DIR!\test.exe" >nul 2>&1
    del "!TEMP_DIR!\test.cpp" >nul 2>&1
) else (
    echo [WARNING] Test compilation failed
)

:: Cleanup
echo.
echo Cleaning up temporary files...
if exist "!TEMP_DIR!\mingw.7z" del "!TEMP_DIR!\mingw.7z" >nul 2>&1
if exist "!TEMP_DIR!" rmdir /s /q "!TEMP_DIR!" >nul 2>&1

echo.
echo ========================================
echo        SETUP COMPLETED SUCCESSFULLY!
echo ========================================
echo.
echo MinGW has been installed and configured.
echo You can now build and run the Tetris game!
echo.
echo Next steps:
echo  1. Close this window
echo  2. Open a NEW command prompt
echo  3. Navigate to the game directory
echo  4. Run: build_and_run.bat
echo.
echo ========================================
echo.
pause

:: Ask if user wants to build now
echo.
choice /C YN /M "Do you want to build and run the game now"
if errorlevel 2 goto :end
if errorlevel 1 goto :build_game

:build_game
echo.
echo Building Tetris game...
echo ========================================
call build_and_run.bat
goto :end

:end
echo.
echo Thank you for installing Tetris!
echo.
pause
exit /b 0
