#include "mainwindow.h"
#include "initialwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    InitialWindow initial;
    initial.show();
//    w.show();
    return a.exec();
}
