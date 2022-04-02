#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include "shared.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("Blog_pl_PL");
    a.installTranslator ( &translator );
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
