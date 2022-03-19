#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>

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
};

#endif // INITIALWINDOW_H
