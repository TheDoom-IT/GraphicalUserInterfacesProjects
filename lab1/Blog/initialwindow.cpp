#include "initialwindow.h"
#include "ui_initialwindow.h"

InitialWindow::InitialWindow(QWidget *parent, LoginService* loginService) :
    QMainWindow(parent),
    ui(new Ui::InitialWindow)
{
    ui->setupUi(this);
    ui->rgsSignUpBtn->setEnabled(false);
    ui->loginSignInBtn->setEnabled(false);

    this->loginService = loginService;

    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);

    connect(ui->loginUsernameText, SIGNAL(textChanged(QString)), this, SLOT(signInInputChanged()));
    connect(ui->loginPasswdText, SIGNAL(textChanged(QString)), this, SLOT(signInInputChanged()));

    connect(ui->rgsUsernameText, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
    connect(ui->rgsEmailText, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
    connect(ui->rgsPasswdText, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
    connect(ui->rgsConfPasswdText, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
}

InitialWindow::~InitialWindow()
{
    delete ui;
}

void InitialWindow::resetWindow()
{
    clearSignInPage();
    clearSignUpPage();
    clearInitialPage();
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}

void InitialWindow::on_signInBtn_clicked()
{
    clearSignInPage();
    clearInitialPage();
    ui->stackedWidget->setCurrentIndex((int)Page::LOGIN);
}

void InitialWindow::on_signUpBtn_clicked()
{
    clearSignUpPage();
    clearInitialPage();
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

// enable/disable signIn button
void InitialWindow::signInInputChanged()
{
    QString login = ui->loginUsernameText->text();
    QString password = ui->loginPasswdText->text();

    if(login == "" || password == "")
        return ui->loginSignInBtn->setEnabled(false);

    ui->loginSignInBtn->setEnabled(true);
}

// enable/disable signUp button
void InitialWindow::signUpInputChanged()
{
    QString login = ui->rgsUsernameText->text();
    QString email = ui->rgsEmailText->text();
    QString passwd = ui->rgsPasswdText->text();
    QString confPasswd = ui->rgsConfPasswdText->text();

    if(login.isEmpty() || email.isEmpty() || passwd.isEmpty() || confPasswd.isEmpty())
        return ui->rgsSignUpBtn->setEnabled(false);

    ui->rgsSignUpBtn->setEnabled(true);
}

void InitialWindow::clearSignInPage()
{
    ui->loginUsernameText->clear();
    ui->loginPasswdText->clear();
    ui->loginInfoText->clear();
    ui->loginSignInBtn->setEnabled(false);
}

void InitialWindow::clearSignUpPage()
{
    ui->rgsUsernameText->clear();
    ui->rgsEmailText->clear();
    ui->rgsPasswdText->clear();
    ui->rgsConfPasswdText->clear();
    ui->rgsInfoText->clear();
    ui->rgsSignUpBtn->setEnabled(false);
}

void InitialWindow::clearInitialPage()
{
    ui->initialInfoText->clear();
}

// create a new account
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
    ui->initialInfoText->setText(tr("Succesfully created a new account. You can now log in."));
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}


// log in
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
