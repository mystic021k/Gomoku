#pragma once

#include <QtWidgets/QMainWindow>
#include "gomokuengine.h"
#include "ui_gomoku.h"

class Gomoku : public QMainWindow
{
    Q_OBJECT

public:
    Gomoku(QWidget *parent = nullptr);
    ~Gomoku();

    void paintBoard();
    void checkResult();
    void resizeEvent(QResizeEvent* event);
    void startGame();
    void nextTurn();
    void changeButtonState(bool enabled);
    void setStatusMsg();
public slots:
    void playerSetPiece(QPoint* pos);
    void onTimer();
    void playerTakeBlack();
    void playerTakeWhite();
    void playerToPlayer();
    void ShowAbout();
    void ShowHelp();
private:
    Ui::GomokuClass ui;
    GomokuEngine* engine;
    QTimer* timer;
    int pieceSize;
    int leftStart;
    int topStart;
    int currentTurn;
    int playerTurn = 0;
    int playerOrComputer[2] = {0, 0};
    bool isFinished = false;
    bool buttonEnabled = true;
};
