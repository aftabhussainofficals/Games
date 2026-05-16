#include "../include/game/Game.h"
#include "../include/db/ScoreDB.h"

int main() {
    setupConsole();

    vector<PlayerRecord> records = loadScores();

    clearScreen(); moveTop();
    cout << "\n\n  Enter your name: ";
    string playerName;
    getline(cin, playerName);
    if (playerName.empty()) playerName = "Player";

    while (true) {
        Menu mainMenu(false);
        if (mainMenu.run() == 1) break;

        Menu modeMenu(true);
        bool challenge = (modeMenu.run() == 1);

        showCountdown();

        Game game(challenge);
        string mode;
        if (challenge) {
            mode = "Challenge";
        } else {
            mode = "Normal";
        }
        game.run(records, playerName, mode);
    }

    clearScreen(); moveTop();
    cout << "Goodbye!\n";
    return 0;
}
