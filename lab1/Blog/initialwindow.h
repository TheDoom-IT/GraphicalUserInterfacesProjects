#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>
#include "services/login.h"

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
    explicit InitialWindow(QWidget *parent, LoginService* loginService);
    ~InitialWindow();

signals:
    void loggedIn();

private slots:
    // navigation buttons
    void on_signInBtn_clicked();
    void on_signUpBtn_clicked();

    void on_loginSignInBtn_clicked();
    void on_loginBackBtn_clicked();

    void on_rgsSignUpBtn_clicked();
    void on_rgsBackBtn_clicked();

private:
    Ui::InitialWindow *ui;
    LoginService* loginService;
};

#endif // INITIALWINDOW_H
