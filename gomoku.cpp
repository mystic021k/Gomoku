#include "gomoku.h"
#include "gomokuai.h"
#include "qgamehelpdlg.h"
#include <QMessageBox>
#include <QTimer>

Gomoku::Gomoku(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.graphicsView, SIGNAL(set_piece(QPoint*)), this, SLOT(playerSetPiece(QPoint*)));
    connect(ui.action_black, SIGNAL(triggered()), this, SLOT(playerTakeBlack()));
    connect(ui.action_white, SIGNAL(triggered()), this, SLOT(playerTakeWhite()));
    connect(ui.action_duel, SIGNAL(triggered()), this, SLOT(playerToPlayer()));
    connect(ui.action_about, SIGNAL(triggered()), this, SLOT(ShowAbout()));
    connect(ui.action_help, SIGNAL(triggered()), this, SLOT(ShowHelp()));
    timer = new QTimer(this);
    timer->start(0);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    playerTakeBlack();
}

Gomoku::~Gomoku()
{}

void Gomoku::paintBoard()
{
    if (engine != nullptr)
    {
        int minLength = this->width() <= this->height() - 56 ? this->width() : this->height() - 56;
        int pieceRoughSize = (minLength - minLength % 110) / 11;
        pieceSize = pieceRoughSize - pieceRoughSize % 10;
        leftStart = (this->width() - pieceSize * 11) / 2;
        topStart = (this->height() - 56 - pieceSize * 11) / 2;
        QGraphicsScene* scene = new QGraphicsScene(this);
        QPen backPen;
        backPen.setColor(Qt::red);
        backPen.setWidth(5);
        backPen.setStyle(Qt::SolidLine);
        QBrush backBrush;
        backBrush.setColor(Qt::yellow);
        backBrush.setStyle(Qt::SolidPattern);
        scene->addRect(leftStart, topStart, 11 * pieceSize, 11 * pieceSize, backPen, backBrush);
        for (int s = 0; s <= 11; s++)
        {
            QPen linePen;
            linePen.setColor(Qt::red);
            linePen.setStyle(Qt::SolidLine);
            scene->addLine(leftStart + 0, topStart + s * pieceSize, leftStart + 11 * pieceSize, topStart + s * pieceSize, linePen);
            scene->addLine(leftStart + s * pieceSize, topStart + 0, leftStart + s * pieceSize, topStart + 11 * pieceSize, linePen);
        }
        for (int m = 0; m < 10; m++)
        {
            for (int n = 0; n < 10; n++)
            {
                QPoint centerPos = QPoint((m + 1) * pieceSize, (n + 1) * pieceSize);
                int chessRadius = pieceSize * 0.4;
                if (engine->getBoardNum(m, n) == 1)
                {
                    QPen piecePen;
                    piecePen.setStyle(Qt::NoPen);
                    QRadialGradient radialGrad(QPointF(leftStart + centerPos.x() - chessRadius / 4, topStart + centerPos.y() - chessRadius / 4), chessRadius);
                    radialGrad.setColorAt(0, Qt::darkGray);
                    radialGrad.setColorAt(1, Qt::black);
                    QBrush pieceBrush(radialGrad);
                    scene->addEllipse(leftStart + centerPos.x() - chessRadius, topStart + centerPos.y() - chessRadius, chessRadius * 2, chessRadius * 2, piecePen, pieceBrush);
                }
                if (engine->getBoardNum(m, n) == 2)
                {
                    QPen piecePen;
                    piecePen.setStyle(Qt::NoPen);
                    QRadialGradient radialGrad(QPointF(leftStart + centerPos.x() - chessRadius / 12, topStart + centerPos.y() - chessRadius / 12), chessRadius);
                    radialGrad.setColorAt(0, Qt::white);
                    radialGrad.setColorAt(0.8, Qt::white);
                    radialGrad.setColorAt(1, Qt::lightGray);
                    QBrush pieceBrush(radialGrad);
                    scene->addEllipse(leftStart + centerPos.x() - chessRadius, topStart + centerPos.y() - chessRadius, chessRadius * 2, chessRadius * 2, piecePen, pieceBrush);
                }
            }
        }
        ui.graphicsView->setScene(scene);
    }
}

void Gomoku::checkResult()
{
    int gameResult = engine->checkResult();
    if(gameResult == engine->CONTINUE)
    {
        return;
    }
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromUtf8("五子棋"));
    if(gameResult == engine->TIE)
    {
        msgBox.setText(QString::fromUtf8("不分胜负　"));
        ui.statusBar->showMessage(QString::fromUtf8("不分胜负"));
    }
    if(gameResult == engine->BLACK_WIN)
    {
        msgBox.setText(QString::fromUtf8("黑棋胜利　"));
        ui.statusBar->showMessage(QString::fromUtf8("黑棋胜利"));
    }
    if(gameResult == engine->WHITE_WIN)
    {
        msgBox.setText(QString::fromUtf8("白棋胜利　"));
        ui.statusBar->showMessage(QString::fromUtf8("白棋胜利"));
    }
    msgBox.exec();
    changeButtonState(true);
    isFinished = true;
}

void Gomoku::playerSetPiece(QPoint* pos)
{
    if(isFinished)
    {
        return;
    }
    if(playerOrComputer[currentTurn] != 1)
    {
        return;
    }
    int m = (int)floor((pos->x() - leftStart - pieceSize / 2) / pieceSize);
    int n = (int)floor((pos->y() - topStart - pieceSize / 2) / pieceSize);
    bool doSuccess = false;
    if(currentTurn == 0)
    {
        doSuccess = engine->blackTurn(m,n);
    }
    if(currentTurn == 1)
    {
        doSuccess = engine->whiteTurn(m,n);
    }
    if (!doSuccess)
    {
        return;
    }
    paintBoard();
    nextTurn();
    checkResult();
}

void Gomoku::resizeEvent(QResizeEvent* event)
{
    ui.graphicsView->setGeometry(0, 0, this->width(), this->height() - 56);
    paintBoard();
}

void Gomoku::startGame()
{
    engine = new GomokuEngine();
    engine->newGame();
    currentTurn = 0;
    isFinished = false;
    paintBoard();
    setStatusMsg();
}

void Gomoku::nextTurn()
{
    currentTurn++;
    currentTurn = currentTurn % 2;
    if(buttonEnabled)
    {
        changeButtonState(false);
    }
    setStatusMsg();
}

void Gomoku::changeButtonState(bool enabled)
{
    ui.action_black->setEnabled(enabled);
    ui.action_white->setEnabled(enabled);
    ui.action_duel->setEnabled(enabled);
    buttonEnabled = enabled;
}

void Gomoku::setStatusMsg()
{
    if(currentTurn == 0)
    {
        ui.statusBar->showMessage(QString::fromUtf8("黑棋走"));
    }
    else if(currentTurn == 1)
    {
        ui.statusBar->showMessage(QString::fromUtf8("白棋走"));
    }
}

void Gomoku::onTimer()
{
    if(isFinished)
    {
        return;
    }
    if(playerOrComputer[currentTurn] == 0)
    {
        if(currentTurn == 0)
        {
            GomokuAI* ai = new GomokuAI(engine);
            ai->doBlackTurn();
            paintBoard();
            nextTurn();
            checkResult();
        }
        else if(currentTurn == 1)
        {
            GomokuAI* ai = new GomokuAI(engine);
            ai->doWhiteTurn();
            paintBoard();
            nextTurn();
            checkResult();
        }
    }
}

void Gomoku::playerTakeBlack()
{
    playerOrComputer[0] = 1;
    playerOrComputer[1] = 0;
    startGame();
}

void Gomoku::playerTakeWhite()
{
    playerOrComputer[0] = 0;
    playerOrComputer[1] = 1;
    startGame();
}

void Gomoku::playerToPlayer()
{
    playerOrComputer[0] = 1;
    playerOrComputer[1] = 1;
    startGame();
}

void Gomoku::ShowAbout()
{
    QMessageBox::about(this, QString(), "Version 1.0.0\r\n2024.10.29");
}

void Gomoku::ShowHelp()
{
    QGameHelpDlg dlg;
    dlg.exec();
}
