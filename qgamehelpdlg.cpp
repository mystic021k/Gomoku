#include "qgamehelpdlg.h"

QGameHelpDlg::QGameHelpDlg(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    ui.textBrowser->setHtml(QString::fromUtf8("五子棋，是一种两人对弈的纯策略型棋类游戏，通常双方分别使用黑白两色的棋子，轮流下在棋盘直线与横线的交叉点上，先在横线、直线或斜对角线上形成5子连线者获胜。<br>在此一律黑棋先走，玩家可选择执黑棋还是白棋来决定是否先走，选择后另一方将由电脑来控制。或者可以选择对战，但此时是黑棋白棋双方都由玩家来控制。<br>该版本没有禁手规则，可以放心用任何办法来赢棋。<br>"));
}

QGameHelpDlg::~QGameHelpDlg()
{}

void QGameHelpDlg::resizeEvent(QResizeEvent* event)
{
    ui.textBrowser->setGeometry(0, 0, this->width(), this->height());
}
