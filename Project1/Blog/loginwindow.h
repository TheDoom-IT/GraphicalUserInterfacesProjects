#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = nullptr);
    ~LogInWindow();

private:
    Ui::LogInWindow *ui;
};

#endif // LOGINWINDOW_H
