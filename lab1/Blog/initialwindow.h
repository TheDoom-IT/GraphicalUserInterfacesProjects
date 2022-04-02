#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>
#include "services/loginservice.h"

namespace Ui {
class InitialWindow;
}

class InitialWindow : public QMainWindow
{
    Q_OBJECT

    enum class Page {
        INITIAL = 0,
        LOGIN = 1,
        REGISTER = 2
    };

public:
    explicit InitialWindow(QWidget *parent, LoginService* loginService);
    ~InitialWindow();

    void resetWindow();

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

    void signInInputChanged();
    void signUpInputChanged();

private:
    Ui::InitialWindow *ui;
    LoginService* loginService;

    void clearSignInPage();
    void clearSignUpPage();
    void clearInitialPage();
};

#endif // INITIALWINDOW_H
