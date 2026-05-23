#pragma once
#include "BaseGame.h"
#include "GameTime.h"
#include "../../include/db/ScoreDB.h"

class Game : public BaseGame {
public:
    // kept for GameLogic/GameDraw that still reference it
    bool isChallengeMember;

    static const int CHALLENGE_SECS = 300;
    static const int TARGET_SCORE   = 1500;

    Game(bool challenge);
    void run(vector<PlayerRecord>& records, string playerName, string mode);

    virtual bool   isGameOver()       const override { return gameOver; }
    virtual string getTimeDisplay()   const override;
    virtual bool   isChallenge()      const override { return false; }
};
