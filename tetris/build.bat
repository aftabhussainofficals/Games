@echo off
taskkill /F /IM tetris.exe >nul 2>&1
g++ src/main.cpp src/ui/tetris.cpp src/ui/colors.cpp src/ui/Menu.cpp src/data/piecedata.cpp src/core/Piece.cpp src/core/Board.cpp src/game/Game.cpp src/game/GameTime.cpp src/game/GameLogic.cpp src/game/GameInput.cpp src/game/GameDraw.cpp src/db/ScoreDB.cpp -I include/ui -I include/core -I include/game -I include/db -o tetris.exe
if %errorlevel% equ 0 (
    echo Build successful!
) else (
    echo Build failed!
)
