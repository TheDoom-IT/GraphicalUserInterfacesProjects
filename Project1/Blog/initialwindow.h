#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>

enum class Page {
    INITIAL = 0,
    LOGIN = 1,
    REGISTER = 2
};

namespace Ui {
class InitialWindow;
}

class InitialWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitialWindow(QWidget *parent = nullptr);
    ~InitialWindow();

signals:
    void openMainWindow();

private slots:
    // navigation buttons
    void on_signInBtn_clicked();

    void on_signUpBtn_clicked();

    void on_loginBackBtn_clicked();

    void on_rgsBackBtn_clicked();

    // action buttons
    void signIn();

    void signUp();

private:
    Ui::InitialWindow *ui;
};

#endif // INITIALWINDOW_H
