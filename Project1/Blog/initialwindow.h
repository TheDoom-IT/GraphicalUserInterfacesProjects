#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"

namespace Ui {
class InitialWindow;
}

class InitialWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitialWindow(QWidget *parent = nullptr);
    ~InitialWindow();

private:
    Ui::InitialWindow *ui;
    LogInWindow *login;
};

#endif // INITIALWINDOW_H
