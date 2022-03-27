#include "initialwindow.h"
#include "ui_initialwindow.h"

InitialWindow::InitialWindow(QWidget *parent, LoginService* loginService) :
    QMainWindow(parent),
    ui(new Ui::InitialWindow)
{
    ui->setupUi(this);

    this->loginService = loginService;

    // INITIAL is a default page
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}

InitialWindow::~InitialWindow()
{
    delete ui;
}

void InitialWindow::on_signInBtn_clicked()
{
    ui->loginUsernameText->setText("");
    ui->loginPasswdText->setText("");
    ui->loginInfoText->setText("");
    ui->stackedWidget->setCurrentIndex((int)Page::LOGIN);
}

void InitialWindow::on_signUpBtn_clicked()
{
    ui->rgsUsernameText->setText("");
    ui->rgsEmailText->setText("");
    ui->rgsPasswdText->setText("");
    ui->rgsConfPasswdText->setText("");
    ui->rgsInfoText->setText("");
    ui->stackedWidget->setCurrentIndex((int)Page::REGISTER);
}

void InitialWindow::on_loginBackBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}

void InitialWindow::on_rgsBackBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}

void InitialWindow::on_rgsSignUpBtn_clicked()
{
    QString username = ui->rgsUsernameText->text();
    QString email = ui->rgsEmailText->text();
    QString password = ui->rgsPasswdText->text();
    QString confPassword = ui->rgsConfPasswdText->text();

    std::pair<bool, QString> result = loginService->signUp(username, email, password, confPassword);

    if(!result.first)
    {
        // show error information
        ui->rgsInfoText->setText(result.second);
        return;
    }

    // show information on the initial window about successful signing up
    ui->initialInfoText->setText(tr("Succesfully created new accout. You can now log in."));
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}

void InitialWindow::on_loginSignInBtn_clicked()
{
    QString username = ui->loginUsernameText->text();
    QString password = ui->loginPasswdText->text();

    auto result = loginService->signIn(username, password);

    if(!result.first)
    {
        ui->loginInfoText->setText(result.second);
        return;
    }

    emit loggedIn();
}
