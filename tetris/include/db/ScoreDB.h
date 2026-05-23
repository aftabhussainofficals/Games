#pragma once
#include "../../include/ui/tetris.h"

class PlayerRecord {
private:
    string name;
    int    games;
    int    highScore;
    int    highLevel;
    string lastMode;

public:
    PlayerRecord() : games(0), highScore(0), highLevel(1), lastMode("Normal") {}
    PlayerRecord(string n, int g, int hs, int hl, string lm)
        : name(n), games(g), highScore(hs), highLevel(hl), lastMode(lm) {}

    string getName()      const { return name; }
    int    getGames()     const { return games; }
    int    getHighScore() const { return highScore; }
    int    getHighLevel() const { return highLevel; }
    string getLastMode()  const { return lastMode; }

    void setName(string n)      { name = n; }
    void setLastMode(string lm) { lastMode = lm; }
    void incrementGames()       { games++; }
    void updateHighScore(int s) { if (s > highScore) highScore = s; }
    void updateHighLevel(int l) { if (l > highLevel) highLevel = l; }
};

vector<PlayerRecord> loadScores();
void saveScores(vector<PlayerRecord>& records);
void updatePlayer(vector<PlayerRecord>& records, string name, int score, int level, string mode);
