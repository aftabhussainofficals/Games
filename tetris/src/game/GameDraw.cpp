#include "../../include/game/GameDraw.h"
#include "../../include/game/GameTime.h"

vector<string> buildPanel(Game& game) {
    vector<string> panel;

    panel.push_back(pad16("  NEXT:"));

    for (int row = 0; row < 4; row++) {
        string line = "  ";
        for (int col = 0; col < 4; col++) {
            bool hasTile = (row < game.nextPiece.shape.size() &&
                            col < game.nextPiece.shape[row].size() &&
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

    string timeStr;
    if (game.isChallenge)
        timeStr = formatTime(remainingSeconds(game.startTime, game.CHALLENGE_SECS));
    else
        timeStr = formatTime(elapsedSeconds(game.startTime));
    panel.push_back(pad16("  TMR:" + timeStr));

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

        if (row < panel.size())
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

void showGameOver(Game& game, vector<PlayerRecord>& records, string playerName) {
    clearScreen();
    moveTop();

    bool   isWin     = game.isChallenge && game.score >= game.TARGET_SCORE;
    string color;
    if (isWin) {
        color = colorCode(32);
    } else {
        color = colorCode(31);
    }
    
    string title;
    if (isWin) {
        title = "YOU WIN!";
    } else {
        title = "GAME OVER";
    }
    
    int timeVal;
    if (game.isChallenge) {
        timeVal = remainingSeconds(game.startTime, game.CHALLENGE_SECS);
    } else {
        timeVal = elapsedSeconds(game.startTime);
    }

    const int BOX_WIDTH = 32;
    string equalLine = "", dashLine = "";
    for (int i = 0; i < BOX_WIDTH; i++) equalLine += "\u2550";
    for (int i = 0; i < 26;  i++) dashLine += "\u2500";

    int leftPad  = (26 - title.size()) / 2;
    int rightPad = 26 - title.size() - leftPad;

    // ── game result ───────────────────────────────────────────────────────────
    cout << color << "\u2554" << equalLine << "\u2557\n" << resetStr();
    printBoxRow(string(BOX_WIDTH, ' '), BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow("  \u250c" + dashLine + "\u2510  ", BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow("  \u2502" + string(leftPad,' ') + title + string(rightPad,' ') + "\u2502  ", BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow("  \u2514" + dashLine + "\u2518  ", BOX_WIDTH, BOX_WIDTH, color);
    printBoxRow(string(BOX_WIDTH, ' '), BOX_WIDTH, BOX_WIDTH, color);
    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();

    string scoreLine = "  Score : " + to_string(game.score);
    string levelLine = "  Level : " + to_string(game.level);
    string timeLine  = "  Time  : " + formatTime(timeVal);
    printBoxRow(scoreLine, scoreLine.size(), BOX_WIDTH, color);
    printBoxRow(levelLine, levelLine.size(), BOX_WIDTH, color);
    printBoxRow(timeLine,  timeLine.size(),  BOX_WIDTH, color);

    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();

    // ── leaderboard inside same box ───────────────────────────────────────────
    string lbHeader = "  LEADERBOARD";
    printBoxRow(lbHeader, lbHeader.size(), BOX_WIDTH, color);
    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();

    if (records.empty()) {
        printBoxRow("  No scores yet.", 16, BOX_WIDTH, color);
    } else {
        // sort by highScore descending
        vector<PlayerRecord> sorted = records;
        for (int i = 0; i < sorted.size() - 1; i++)
            for (int j = 0; j < sorted.size() - 1 - i; j++)
                if (sorted[j].highScore < sorted[j+1].highScore)
                    swap(sorted[j], sorted[j+1]);

        // find current player position
        int playerPos = -1;
        for (int i = 0; i < sorted.size(); i++) {
            if (sorted[i].name == playerName) {
                playerPos = i;
                break;
            }
        }

        // show top 10 or include player if outside top 10
        int displayCount = 10;
        if (sorted.size() < displayCount) {
            displayCount = sorted.size();
        }
        
        bool playerInTop10 = (playerPos >= 0 && playerPos < 10);

        string hdr = "  Name        Score  Lvl Mode";
        printBoxRow(hdr, hdr.size(), BOX_WIDTH, color);

        for (int i = 0; i < displayCount; i++) {
            string name = sorted[i].name;
            if (name.size() > 10) name = name.substr(0, 10);
            name += string(10 - name.size(), ' ');

            string scoreStr = to_string(sorted[i].highScore);
            string levelStr = to_string(sorted[i].highLevel);
            string mode;
            if (sorted[i].lastMode.size() >= 4) {
                mode = sorted[i].lastMode.substr(0, 4);
            } else {
                mode = sorted[i].lastMode;
            }
            
            int scorePad = 5 - scoreStr.size();
            if (scorePad < 0) scorePad = 0;
            scoreStr = string(scorePad, ' ') + scoreStr;
            
            int levelPad = 3 - levelStr.size();
            if (levelPad < 0) levelPad = 0;
            levelStr = string(levelPad, ' ') + levelStr;

            string row = "  " + name + "  " + scoreStr + "  " + levelStr + " " + mode;
            
            int pad = BOX_WIDTH - row.size();
            if (pad < 0) pad = 0;
            
            if (sorted[i].name == playerName)
                cout << color << "\u2551" << resetStr() << colorCode(32)
                     << row << string(pad, ' ') << resetStr()
                     << color << "\u2551\n" << resetStr();
            else if (i == 0)
                cout << color << "\u2551" << resetStr() << colorCode(33)
                     << row << string(pad, ' ') << resetStr()
                     << color << "\u2551\n" << resetStr();
            else
                printBoxRow(row, row.size(), BOX_WIDTH, color);
        }

        // if player is outside top 10, show them at the end
        if (!playerInTop10 && playerPos >= 0) {
            printBoxRow("  ...", 5, BOX_WIDTH, color);
            
            string name = sorted[playerPos].name;
            if (name.size() > 10) name = name.substr(0, 10);
            name += string(10 - name.size(), ' ');

            string scoreStr = to_string(sorted[playerPos].highScore);
            string levelStr = to_string(sorted[playerPos].highLevel);
            string mode;
            if (sorted[playerPos].lastMode.size() >= 4) {
                mode = sorted[playerPos].lastMode.substr(0, 4);
            } else {
                mode = sorted[playerPos].lastMode;
            }
            
            int scorePad = 5 - scoreStr.size();
            if (scorePad < 0) scorePad = 0;
            scoreStr = string(scorePad, ' ') + scoreStr;
            
            int levelPad = 3 - levelStr.size();
            if (levelPad < 0) levelPad = 0;
            levelStr = string(levelPad, ' ') + levelStr;

            string row = "  " + name + "  " + scoreStr + "  " + levelStr + " " + mode;
            
            int pad = BOX_WIDTH - row.size();
            if (pad < 0) pad = 0;
            
            cout << color << "\u2551" << resetStr() << colorCode(32)
                 << row << string(pad, ' ') << resetStr()
                 << color << "\u2551\n" << resetStr();
        }
    }

    cout << color << "\u2560" << equalLine << "\u2563\n" << resetStr();
    string prompt = "  Press any key to continue...";
    printBoxRow(prompt, prompt.size(), BOX_WIDTH, color);
    cout << color << "\u255a" << equalLine << "\u255d\n" << resetStr();

    cout.flush();
    _getch();
}
