#include "../../include/game/GameTime.h"

int elapsedSeconds(time_t startTime) {
    time_t currentTime = time(nullptr);
    int elapsed = currentTime - startTime;
    return elapsed;
}

int remainingSeconds(time_t startTime, int challengeSecs) {
    int elapsed = elapsedSeconds(startTime);
    int remaining = challengeSecs - elapsed;
    if (remaining < 0) {
        remaining = 0;
    }
    return remaining;
}

string formatTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    string mm = to_string(minutes);
    string ss = to_string(seconds);

    if (minutes < 10) mm = "0" + mm;
    if (seconds < 10) ss = "0" + ss;

    return mm + ":" + ss;
}
