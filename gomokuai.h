#include "gomokuengine.h"

#pragma once
class GomokuAI
{
private:
    GomokuEngine* engine;
public:
    GomokuAI();
    GomokuAI(GomokuEngine* gengine);
    bool doBlackTurn();
    bool doWhiteTurn();
};

