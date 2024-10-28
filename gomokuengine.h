#pragma once
class GomokuEngine
{
public:
    const int CONTINUE = 0;
    const int TIE = 100;
    const int BLACK_WIN = 101;
    const int WHITE_WIN = 102;
    GomokuEngine();
    void newGame();
    bool blackTurn(int m, int n);
    bool whiteTurn(int m, int n);
    int checkResult();
    int getBoardNum(int m, int n);
    bool getBlackBool(int m, int n, int k);
    bool getWhiteBool(int m, int n, int k);
    int getWinNum(int i, int j);
    int getBlackCount();
    int getWhiteCount();
private:
    int board[10][10];
    bool black_table[10][10][192];
    bool white_table[10][10][192];
    int win[2][192];
    int black_count;
    int white_count;
    bool tie;
};

