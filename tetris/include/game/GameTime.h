#pragma once
#include "Game.h"

int    elapsedSeconds(time_t startTime);
int    remainingSeconds(time_t startTime, int challengeSecs);
string formatTime(int totalSeconds);
