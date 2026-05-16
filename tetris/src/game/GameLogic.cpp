#include "../../include/game/GameLogic.h"
#include "../../include/game/GameTime.h"

void spawnNext(Game& game) {
    game.currentPiece = game.nextPiece;
    game.currentPiece.resetPosition();
    game.nextPiece = Piece();

    if (game.board.hasCollision(game.currentPiece, game.currentPiece.col, game.currentPiece.row))
        game.gameOver = true;
}

Grid rotateShape(Grid shape) {
    int rows = shape.size();
    int cols = shape[0].size();

    Grid rotated(cols, vector<int>(rows));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            rotated[c][rows - 1 - r] = shape[r][c];

    return rotated;
}

void tryRotate(Game& game) {
    Grid rotated = rotateShape(game.currentPiece.shape);
    int  kicks[] = { 0, 1, -1 };

    for (int i = 0; i < 3; i++) {
        Piece test = game.currentPiece;
        test.shape = rotated;
        test.col   = game.currentPiece.col + kicks[i];

        if (!game.board.hasCollision(test, test.col, test.row)) {
            game.currentPiece.shape = rotated;
            game.currentPiece.col   = test.col;
            return;
        }
    }
}

void lockAndScore(Game& game) {
    game.board.lockPiece(game.currentPiece);
    int lines = game.board.clearFullLines();

    if (lines > 0) {
        game.score += lines * lines * 100;
        game.level  = game.score / 500 + 1;

        game.gravityDelay = 500 - (game.level - 1) * 40;
        if (game.gravityDelay < 100) game.gravityDelay = 100;
    }

    spawnNext(game);
}

void updateGame(Game& game) {
    if (game.paused || game.gameOver) return;

    if (!game.board.hasCollision(game.currentPiece, game.currentPiece.col, game.currentPiece.row + 1))
        game.currentPiece.row++;
    else
        lockAndScore(game);

    if (game.isChallenge) {
        if (game.score >= game.TARGET_SCORE) game.gameOver = true;
        if (remainingSeconds(game.startTime, game.CHALLENGE_SECS) == 0) game.gameOver = true;
    }
}
