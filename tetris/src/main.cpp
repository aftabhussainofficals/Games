#include "../include/game/Game.h"
#include "../include/game/ChallengeGame.h"
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

        if (challenge) {
            ChallengeGame game;
            game.run(records, playerName, "Challenge");
        } else {
            Game game(false);
            game.run(records, playerName, "Normal");
        }
    }

    clearScreen(); moveTop();
    cout << "Goodbye!\n";
    return 0;
}
