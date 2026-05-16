#pragma once
#include "tetris.h"

string colorCode(int code);
string resetStr();
string boldText(string s);
void   printBoxRow(string content, int visibleLen, int boxWidth, string borderColor);
