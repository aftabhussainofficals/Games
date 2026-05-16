#include "../../include/ui/colors.h"

string colorCode(int code) {
    return "\033[" + to_string(code) + "m";
}

string resetStr() {
    return "\033[0m";
}

string boldText(string s) {
    return "\033[1m" + s + "\033[0m";
}

void printBoxRow(string content, int visibleLen, int boxWidth, string borderColor) {
    int pad = boxWidth - visibleLen;
    if (pad < 0) pad = 0;
    cout << borderColor << "\u2551" << resetStr()
         << content << string(pad, ' ')
         << borderColor << "\u2551\n" << resetStr();
}
