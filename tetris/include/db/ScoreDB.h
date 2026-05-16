#pragma once
#include "../../include/ui/tetris.h"

struct PlayerRecord {
    string name;
    int    games;
    int    highScore;
    int    highLevel;
    string lastMode;
};

vector<PlayerRecord> loadScores();
void saveScores(vector<PlayerRecord>& records);
void updatePlayer(vector<PlayerRecord>& records, string name, int score, int level, string mode);
