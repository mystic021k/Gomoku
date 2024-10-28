#include "gomoku.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gomoku w;
    w.show();
    return a.exec();
}
