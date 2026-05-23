#include "../../include/game/GameDraw.h"
#include "../../include/game/GameTime.h"

vector<string> buildPanel(Game& game) {
    vector<string> panel;

    panel.push_back(pad16("  NEXT:"));

    for (int row = 0; row < 4; row++) {
        string line = "  ";
        for (int col = 0; col < 4; col++) {
            bool hasTile = (row < (int)game.nextPiece.shape.size() &&
                            col < (int)game.nextPiece.shape[row].size() &&
                            game.nextPiece.shape[row][col] != 0);
            if (hasTile)
                line += colorCode(getPieceColor(game.nextPiece.typeIndex)) + "[]" + resetStr();
            else
                line += "  ";
        }
        line += string(6, ' ');
        panel.push_back(line);
    }

    panel.push_back(pad16(""));
    panel.push_back(pad16("  SCR:" + to_string(game.score)));
    panel.push_back(pad16("  LVL:" + to_string(game.level)));
    panel.push_back(pad16("  TMR:" + game.getTimeDisplay()));
    panel.push_back(pad16(""));

    if (game.showControls) {
        panel.push_back(pad16("  A/D:move"));
        panel.push_back(pad16("  W:rotate"));
        panel.push_back(pad16("  S:drop"));
        panel.push_back(pad16("  SPC:hard"));
        panel.push_back(pad16("  P:pause"));
        panel.push_back(pad16("  Q:quit"));
    } else {
        panel.push_back(pad16("  C:controls"));
    }

    return panel;
}

void drawGame(Game& game) {
    moveTop();
    int ghostRow = game.board.getGhostRow(game.currentPiece);
    vector<string> panel = buildPanel(game);

    cout << "\u250c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500"
         << "\u252c"
         << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510\n";

    for (int row = 0; row < Board::HEIGHT; row++) {
        cout << "\u2502";
        game.board.drawRow(row, game.currentPiece, ghostRow);
        cout << "\u2502";

        if (row < (int)panel.size())
            cout << panel[row];
        else
            cout << string(16, ' ');

        cout << "\u2502\n";
    }

    cout << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500"
         << "\u2534"
         << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n";
    cout.flush();
}

// helper: format and print one leaderboard row
static void printEntry(int rank, PlayerRecord& rec, const string& playerName,
                       const string& borderColor, int BOX_WIDTH) {
    string name = rec.getName();
    if ((int)name.size() > 9) name = name.substr(0, 9);
    while ((int)name.size() < 9) name += ' ';

    string sc = to_string(rec.getHighScore());
    while ((int)sc.size() < 5) sc = ' ' + sc;

    string lv = to_string(rec.getHighLevel());
    while ((int)lv.size() < 3) lv = ' ' + lv;

    string md = rec.getLastMode();
    if ((int)md.size() > 4) md = md.substr(0, 4);

    string rk = to_string(rank);
    while ((int)rk.size() < 2) rk = ' ' + rk;

    string row = "  " + rk + " " + name + " " + sc + " " + lv + " " + md;
    int pad = BOX_WIDTH - (int)row.size();
    if (pad < 0) pad = 0;

    string entryColor = (rec.getName() == playerName) ? colorCode(32)
                      : (rank == 1)                   ? colorCode(33)
                                                      : resetStr();

    cout << borderColor << "\u2551" << resetStr()
         << entryColor << row << string(pad, ' ') << resetStr()
         << borderColor << "\u2551\n" << resetStr();
}

void showGameOver(Game& game, vector<PlayerRecord>& records, string playerName) {
    clearScreen();
    moveTop();

    bool   isWin  = game.isChallenge() && game.score >= game.TARGET_SCORE;
    string color  = isWin ? colorCode(32) : colorCode(31);
    string title  = isWin ? "YOU WIN!" : "GAME OVER";

    int timeVal = game.isChallenge()
                ? remainingSeconds(game.startTime, game.CHALLENGE_SECS)
                : elapsedSeconds(game.startTime);

    const int BOX_WIDTH = 36;
    string equalLine, dashLine;
    for (int i = 0; i < BOX_WIDTH; i++) equalLine += "\u2550";
    for (int i = 0; i < 30; i++)       dashLine  += "\u2500";

    int leftPad  = (30 - (int)title.size()) / 2;
    int rightPad = 30 - (int)title.size() - leftPad;

    // title box
    cout << color << "\u2554" << equalLine << "\u2557\n" << resetStr();
    printBoxRow(string(BOX_WIDTH, ' '), BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow("  \u250c" + dashLine + "\u2510  ", BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow("  \u2502" + string(leftPad,' ') + title + string(rightPad,' ') + "\u2502  ", BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow("  \u2514" + dashLine + "\u2518  ", BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow(string(BOX_WIDTH, ' '), BOX_WIDTH, BOX_WIDTH, color);
    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();

    // stats
    string scoreLine = "  Score : " + to_string(game.score);
    string levelLine = "  Level : " + to_string(game.level);
    string timeLine  = "  Time  : " + formatTime(timeVal);
    printBoxRow(scoreLine, (int)scoreLine.size(), BOX_WIDTH, color);
    printBoxRow(levelLine, (int)levelLine.size(), BOX_WIDTH, color);
    printBoxRow(timeLine,  (int)timeLine.size(),  BOX_WIDTH, color);
    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();

    // leaderboard
    string lbHeader = "  LEADERBOARD";
    printBoxRow(lbHeader, (int)lbHeader.size(), BOX_WIDTH, color);
    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();

    if (records.empty()) {
        printBoxRow("  No scores yet.", 16, BOX_WIDTH, color);
    } else {
        // sort descending by highScore
        vector<PlayerRecord> sorted = records;
        for (int i = 0; i < (int)sorted.size() - 1; i++)
            for (int j = 0; j < (int)sorted.size() - 1 - i; j++)
                if (sorted[j].getHighScore() < sorted[j+1].getHighScore())
                    swap(sorted[j], sorted[j+1]);

        // find current player rank
        int playerPos = -1;
        for (int i = 0; i < (int)sorted.size(); i++)
            if (sorted[i].getName() == playerName) { playerPos = i; break; }

        int displayCount = (int)sorted.size() < 10 ? (int)sorted.size() : 10;
        bool playerInTop10 = (playerPos >= 0 && playerPos < 10);

        // column header
        string hdr = "  #  Name      Score Lvl Mode";
        printBoxRow(hdr, (int)hdr.size(), BOX_WIDTH, color);

        for (int i = 0; i < displayCount; i++)
            printEntry(i + 1, sorted[i], playerName, color, BOX_WIDTH);

        // show current player below top10 if not already shown
        if (!playerInTop10 && playerPos >= 0) {
            printBoxRow("  ...", 5, BOX_WIDTH, color);
            printEntry(playerPos + 1, sorted[playerPos], playerName, color, BOX_WIDTH);
        }
    }

    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();
    string prompt = "  Press any key to continue...";
    printBoxRow(prompt, (int)prompt.size(), BOX_WIDTH, color);
    cout << color << "\u255a" << equalLine << "\u255d\n" << resetStr();

    cout.flush();
    _getch();
}
