#include "gomokuengine.h"

GomokuEngine::GomokuEngine()
{
}

void GomokuEngine::newGame()
{
    for(int i=0;i<10;i++)          //初始化棋盘状态
    {
        for(int j=0;j<10;j++)
        {
            board[i][j] = 0;
        }
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            for(int k=0;k<192;k++)
            {
                black_table[j][i][k] = false;
                white_table[j][i][k] = false;
            }
        }
    }
    int count = 0;
    for(int i=0;i<10;i++)          //设定水平方向的获胜位置
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<5;k++)
            {
                black_table[j+k][i][count] = true;
                white_table[j+k][i][count] = true;
            }
            count++;
        }
    }
    for(int i=0;i<10;i++)          //设定垂直方向的获胜位置
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<5;k++)
            {
                black_table[i][j+k][count] = true;
                white_table[i][j+k][count] = true;
            }
            count++;
        }
    }
    for(int i=0;i<6;i++)           //设定正对角线方向的获胜位置
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<5;k++)
            {
                black_table[j+k][i+k][count] = true;
                white_table[j+k][i+k][count] = true;
            }
            count++;
        }
    }
    for(int i=0;i<6;i++)           //设定反对角线方向的获胜位置
    {
        for(int j=9;j>=4;j--)
        {
            for(int k=0;k<5;k++)
            {
                black_table[j-k][i+k][count] = true;
                white_table[j-k][i+k][count] = true;
            }
            count++;
        }
    }
    for(int i=0;i<=1;i++)
    {
        for(int j=0;j<192;j++)
        {
            win[i][j] = 0;
        }
    }
    black_count = 0;
    white_count = 0;
    tie = false;
}

bool GomokuEngine::blackTurn(int m, int n)
{
    if(m < 0 || m >= 10 || n < 0 || n >= 10)
    {
        return false;
    }
    if(board[m][n] == 0)      //该格为空格子
    {
        board[m][n] = 1;	  //设定为黑棋的棋子
        black_count++;
        if((black_count == 50) && (white_count == 50))
        {
            tie = true;
        }
        for(int i=0;i<192;i++)
        {
            if(black_table[m][n][i] && win[0][i] != 7)
            {
                win[0][i]++;
            }
            if(white_table[m][n][i])
            {
                white_table[m][n][i] = false;
                win[1][i]=7;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool GomokuEngine::whiteTurn(int m, int n)
{
    if(m < 0 || m >= 10 || n < 0 || n >= 10)
    {
        return false;
    }
    if(board[m][n] == 0)      //该格为空格子
    {
        board[m][n] = 2;      //设定为白棋的棋子
        white_count++;
        if((white_count == 50) && (black_count == 50))
        {
            tie = true;
        }
        for(int i=0;i<192;i++)
        {
            if(white_table[m][n][i] && win[1][i] != 7)
            {
                win[1][i]++;
            }
            if(black_table[m][n][i])
            {
                black_table[m][n][i] = false;
                win[0][i]=7;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

int GomokuEngine::checkResult()
{
    if(tie)
    {
        return TIE;
    }
    for(int i=0;i<=1;i++)
    {
        for(int j=0;j<192;j++)
        {
            if(win[i][j] == 5)
            {
                if(i==0)           //黑棋获胜
                {
                    return BLACK_WIN;
                }
                else               //白棋获胜
                {
                    return WHITE_WIN;
                }
            }
        }
    }
    return CONTINUE;
}

int GomokuEngine::getBoardNum(int m, int n)
{
    return board[m][n];
}

bool GomokuEngine::getBlackBool(int m, int n, int k)
{
    return black_table[m][n][k];
}

bool GomokuEngine::getWhiteBool(int m, int n, int k)
{
    return white_table[m][n][k];
}

int GomokuEngine::getWinNum(int i, int j)
{
    return win[i][j];
}

int GomokuEngine::getBlackCount()
{
    return black_count;
}

int GomokuEngine::getWhiteCount()
{
    return white_count;
}
