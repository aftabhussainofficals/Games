#pragma once
#include "Game.h"
#include "Timer.h"

class ChallengeGame : public Game {
public:
    Timer timer;  

    static const int CHALLENGE_SECS = 300;
    static const int TARGET_SCORE   = 1500;

    ChallengeGame() : Game(true), timer(CHALLENGE_SECS) {}

    
    virtual bool isGameOver() const override {
        return gameOver || timer.expired() || score >= TARGET_SCORE;
    }

    
    virtual string getTimeDisplay() const override {
        return timer.formatted();
    }

    virtual bool isChallenge() const override { return true; }

    bool hasWon() const { return score >= TARGET_SCORE; }
};
