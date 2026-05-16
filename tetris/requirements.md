# Tetris Game - Setup Guide

## Automated Setup (Easiest Method) ⚡

### Just One Click!

1. Right-click `setup.bat`
2. Select **"Run as administrator"**
3. Wait for automatic installation
4. Play the game!

**The setup script will automatically:**
- ✅ Check for existing MinGW installation
- ✅ Download MinGW compiler if needed (~50 MB)
- ✅ Install MinGW to C:\mingw64
- ✅ Add MinGW to system PATH
- ✅ Verify installation with test compilation
- ✅ Offer to build and run the game immediately

**No manual configuration needed!**

### Requirements for Automated Setup
- Windows 7 or newer (Windows 10/11 recommended)
- Internet connection (for downloading MinGW)
- Administrator privileges
- 100 MB free disk space

---

## Manual Setup (If Automated Setup Fails)

### What You Need

- Windows computer (Windows 7 or newer)
- Internet connection (only for initial setup)
- 50 MB free disk space

## Step-by-Step Setup

### Step 1: Install MinGW (C++ Compiler)

1. Download MinGW installer from: https://sourceforge.net/projects/mingw-w64/files/
2. Choose: **x86_64-posix-seh** version
3. Install to: `C:\mingw64` (remember this location)
4. Wait for installation to complete

### Step 2: Add MinGW to System PATH

1. Press `Windows Key` and search for "Environment Variables"
2. Click "Edit the system environment variables"
3. Click "Environment Variables" button
4. Under "System variables", find and select "Path"
5. Click "Edit"
6. Click "New"
7. Add: `C:\mingw64\bin` (or wherever you installed MinGW)
8. Click "OK" on all windows
9. **Restart your computer** (important!)

### Step 3: Verify Installation

1. Open Command Prompt (search for "cmd")
2. Type: `g++ --version`
3. You should see version information (not an error)

### Step 4: Download the Game

1. Download or clone this repository
2. Extract to a folder like: `C:\Users\YourName\Desktop\tetris`

### Step 5: Build and Run

1. Open Command Prompt
2. Navigate to the game folder:
   ```
   cd C:\Users\YourName\Desktop\tetris
   ```
3. Run the build script:
   ```
   build_and_run.bat
   ```
4. The game will compile and start automatically!

## Troubleshooting

### "g++ is not recognized as a command"
- You didn't add MinGW to PATH correctly
- Make sure you restarted your computer after Step 2
- Check that `C:\mingw64\bin` exists and contains `g++.exe`

### "Build failed" or compilation errors
- Make sure all files are extracted properly
- Check that you're in the correct folder
- Try running Command Prompt as Administrator

### Game doesn't display colors
- Update to Windows 10 or later for best experience
- Colors work best on Windows 10/11

### Can't find the game folder
- Use `dir` command to list files
- Use `cd..` to go back one folder
- Use `cd foldername` to enter a folder

## That's It!

Once setup is complete, you can run the game anytime by:
1. Opening Command Prompt
2. Going to the game folder
3. Running: `tetris.exe`

No internet connection needed to play!
