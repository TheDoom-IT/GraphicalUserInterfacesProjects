#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include "shared.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int ret;
    try {
        MainWindow w;
        w.show();
        ret =  a.exec();
    }
    catch (std::runtime_error & e)
    {
        showInfoDialog(a.tr("Error"), e.what());
        return 1;
    }

    return ret;
}
