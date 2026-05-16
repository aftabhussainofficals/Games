#pragma once
#include "Game.h"
#include "../../include/db/ScoreDB.h"

vector<string> buildPanel(Game& game);
void drawGame(Game& game);
void showGameOver(Game& game, vector<PlayerRecord>& records, string playerName);
