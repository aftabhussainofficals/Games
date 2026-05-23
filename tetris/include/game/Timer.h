#pragma once
#include "../ui/tetris.h"

class Timer {
private:
    time_t startTime;
    int    durationSecs;

public:
    Timer(int duration) : durationSecs(duration) {
        startTime = time(nullptr);
    }

    int elapsed()   const { return (int)(time(nullptr) - startTime); }
    int remaining() const {
        int r = durationSecs - elapsed();
        return r < 0 ? 0 : r;
    }
    bool expired()  const { return remaining() == 0; }

    string formatted() const {
        int t  = remaining();
        int mm = t / 60, ss = t % 60;
        string m = (mm < 10 ? "0" : "") + to_string(mm);
        string s = (ss < 10 ? "0" : "") + to_string(ss);
        return m + ":" + s;
    }
};
