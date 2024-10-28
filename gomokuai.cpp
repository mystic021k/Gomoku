#include "gomokuai.h"

GomokuAI::GomokuAI()
{
}

GomokuAI::GomokuAI(GomokuEngine* gengine)
{
    this->engine = gengine;
}

bool GomokuAI::doBlackTurn()
{
    int m=0,n=0;
    int black_grades[10][10],white_grades[10][10],black_grade=0,white_grade=0;
    int mat=0,nat=0,mde=0,nde=0;
    for(int i=0;i<=9;i++)        //计算玩家在空格子上的获胜分数
    {
        for(int j=0;j<=9;j++)
        {
            white_grades[i][j]=0;
            if(engine->getBoardNum(i, j) == 0)
            {
                for(int k=0;k<192;k++)
                {
                    if(engine->getWhiteBool(i, j, k))
                    {
                        switch(engine->getWinNum(1, k))
                        {
                        case 1:
                            white_grades[i][j]+=5;
                            break;
                        case 2:
                            white_grades[i][j]+=50;
                            break;
                        case 3:
                            white_grades[i][j]+=100;
                            break;
                        case 4:
                            white_grades[i][j]+=400;
                            break;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<=9;i++)        //计算计算机在空格子上的获胜分数
    {
        for(int j=0;j<=9;j++)
        {
            black_grades[i][j]=0;
            if(engine->getBoardNum(i, j) == 0)
            {
                for(int k=0;k<192;k++)
                {
                    if(engine->getBlackBool(i, j, k))
                    {
                        switch(engine->getWinNum(0, k))
                        {
                        case 1:
                            black_grades[i][j]+=5;
                            break;
                        case 2:
                            black_grades[i][j]+=50;
                            break;
                        case 3:
                            black_grades[i][j]+=100;
                            break;
                        case 4:
                            black_grades[i][j]+=400;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(engine->getBlackCount() == 0)              //游戏开始
    {
        if(engine->getBoardNum(4, 4)==0)
        {
            m = 4;
            n = 4;
        }
        else
        {
            m = 5;
            n = 5;
        }
    }
    else
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(engine->getBoardNum(i, j) == 0)
                {
                    if(black_grades[i][j]>=black_grade)
                    {
                        black_grade = black_grades[i][j];
                        mat = i;
                        nat = j;
                    }
                    if(white_grades[i][j]>=white_grade)
                    {
                        white_grade = white_grades[i][j];
                        mde = i;
                        nde = j;
                    }
                }
            }
        }
        if(black_grade>=white_grade)     //攻击
        {
            m = mat;
            n = nat;
        }
        else                   //防守
        {
            m = mde;
            n = nde;
        }
    }
    return engine->blackTurn(m, n);      //设定为计算机的棋子
}

bool GomokuAI::doWhiteTurn()
{
    int m=0,n=0;
    int black_grades[10][10],white_grades[10][10],black_grade=0,white_grade=0;
    int mat=0,nat=0,mde=0,nde=0;
    for(int i=0;i<=9;i++)        //计算玩家在空格子上的获胜分数
    {
        for(int j=0;j<=9;j++)
        {
            black_grades[i][j]=0;
            if(engine->getBoardNum(i, j) == 0)
            {
                for(int k=0;k<192;k++)
                {
                    if(engine->getBlackBool(i, j, k))
                    {
                        switch(engine->getWinNum(0, k))
                        {
                        case 1:
                            black_grades[i][j]+=5;
                            break;
                        case 2:
                            black_grades[i][j]+=50;
                            break;
                        case 3:
                            black_grades[i][j]+=100;
                            break;
                        case 4:
                            black_grades[i][j]+=400;
                            break;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<=9;i++)        //计算计算机在空格子上的获胜分数
    {
        for(int j=0;j<=9;j++)
        {
            white_grades[i][j]=0;
            if(engine->getBoardNum(i, j) == 0)
            {
                for(int k=0;k<192;k++)
                {
                    if(engine->getWhiteBool(i, j, k))
                    {
                        switch(engine->getWinNum(1, k))
                        {
                        case 1:
                            white_grades[i][j]+=5;
                            break;
                        case 2:
                            white_grades[i][j]+=50;
                            break;
                        case 3:
                            white_grades[i][j]+=100;
                            break;
                        case 4:
                            white_grades[i][j]+=400;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(engine->getWhiteCount() == 0)              //游戏开始
    {
        if(engine->getBoardNum(4, 4)==0)
        {
            m = 4;
            n = 4;
        }
        else
        {
            m = 5;
            n = 5;
        }
    }
    else
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(engine->getBoardNum(i, j) == 0)
                {
                    if(white_grades[i][j]>=white_grade)
                    {
                        white_grade = white_grades[i][j];
                        mat = i;
                        nat = j;
                    }
                    if(black_grades[i][j]>=black_grade)
                    {
                        black_grade = black_grades[i][j];
                        mde = i;
                        nde = j;
                    }
                }
            }
        }
        if(white_grade>=black_grade)     //攻击
        {
            m = mat;
            n = nat;
        }
        else                   //防守
        {
            m = mde;
            n = nde;
        }
    }
    return engine->whiteTurn(m, n);      //设定为计算机的棋子
}
