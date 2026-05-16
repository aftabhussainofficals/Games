#include "../../include/game/GameInput.h"
#include "../../include/game/GameLogic.h"

void handleInput(Game& game) {
    while (_kbhit()) {
        char key = readKey();

        if (key == 'q') { game.gameOver = true; return; }
        if (key == 'p') { game.paused = !game.paused; return; }
        if (key == 'c') { game.showControls = !game.showControls; return; }

        if (game.paused) continue;

        if (key == 'a') {
            if (!game.board.hasCollision(game.currentPiece, game.currentPiece.col - 1, game.currentPiece.row))
                game.currentPiece.col--;
        } else if (key == 'd') {
            if (!game.board.hasCollision(game.currentPiece, game.currentPiece.col + 1, game.currentPiece.row))
                game.currentPiece.col++;
        } else if (key == 's') {
            if (!game.board.hasCollision(game.currentPiece, game.currentPiece.col, game.currentPiece.row + 1))
                game.currentPiece.row++;
        } else if (key == 'w') {
            tryRotate(game);
        } else if (key == ' ') {
            while (!game.board.hasCollision(game.currentPiece, game.currentPiece.col, game.currentPiece.row + 1))
                game.currentPiece.row++;
            lockAndScore(game);
        }
    }
}
