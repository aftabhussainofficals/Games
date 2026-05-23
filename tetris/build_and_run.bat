@echo off
g++ tetris/src/main.cpp tetris/src/ui/tetris.cpp tetris/src/ui/colors.cpp tetris/src/ui/Menu.cpp tetris/src/data/piecedata.cpp tetris/src/core/Piece.cpp tetris/src/core/Board.cpp tetris/src/game/Game.cpp tetris/src/game/GameTime.cpp tetris/src/game/GameLogic.cpp tetris/src/game/GameInput.cpp tetris/src/game/GameDraw.cpp tetris/src/db/ScoreDB.cpp -I tetris/include/ui -I tetris/include/core -I tetris/include/game -I tetris/include/db -o tetris.exe
if %errorlevel% == 0 (tetris.exe) else (pause)
