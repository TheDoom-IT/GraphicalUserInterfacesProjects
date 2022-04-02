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

    connect(ui->loginUsernameInput, SIGNAL(textChanged(QString)), this, SLOT(signInInputChanged()));
    connect(ui->loginPasswdInput, SIGNAL(textChanged(QString)), this, SLOT(signInInputChanged()));

    connect(ui->rgsUsernameInput, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
    connect(ui->rgsEmailInput, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
    connect(ui->rgsPasswdInput, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
    connect(ui->rgsConfPasswdInput, SIGNAL(textChanged(QString)), this, SLOT(signUpInputChanged()));
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

void InitialWindow::on_initialSignInBtn_clicked()
{
    clearSignInPage();
    clearInitialPage();
    ui->stackedWidget->setCurrentIndex((int)Page::LOGIN);
}

void InitialWindow::on_initialSignUpBtn_clicked()
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
    QString login = ui->loginUsernameInput->text();
    QString password = ui->loginPasswdInput->text();

    if(login == "" || password == "")
        return ui->loginSignInBtn->setEnabled(false);

    ui->loginSignInBtn->setEnabled(true);
}

// enable/disable signUp button
void InitialWindow::signUpInputChanged()
{
    QString login = ui->rgsUsernameInput->text();
    QString email = ui->rgsEmailInput->text();
    QString passwd = ui->rgsPasswdInput->text();
    QString confPasswd = ui->rgsConfPasswdInput->text();

    if(login.isEmpty() || email.isEmpty() || passwd.isEmpty() || confPasswd.isEmpty())
        return ui->rgsSignUpBtn->setEnabled(false);

    ui->rgsSignUpBtn->setEnabled(true);
}

void InitialWindow::clearSignInPage()
{
    ui->loginUsernameInput->clear();
    ui->loginPasswdInput->clear();
    ui->loginInfoLabel->clear();
    ui->loginSignInBtn->setEnabled(false);
}

void InitialWindow::clearSignUpPage()
{
    ui->rgsUsernameInput->clear();
    ui->rgsEmailInput->clear();
    ui->rgsPasswdInput->clear();
    ui->rgsConfPasswdInput->clear();
    ui->rgsInfoLabel->clear();
    ui->rgsSignUpBtn->setEnabled(false);
}

void InitialWindow::clearInitialPage()
{
    ui->initialInfoLabel->clear();
}

// create a new account
void InitialWindow::on_rgsSignUpBtn_clicked()
{
    QString username = ui->rgsUsernameInput->text();
    QString email = ui->rgsEmailInput->text();
    QString password = ui->rgsPasswdInput->text();
    QString confPassword = ui->rgsConfPasswdInput->text();

    std::pair<bool, QString> result = loginService->signUp(username, email, password, confPassword);

    if(!result.first)
    {
        // show error information
        ui->rgsInfoLabel->setText(result.second);
        return;
    }

    // show information on the initial window about successful signing up
    ui->initialInfoLabel->setText(tr("Succesfully created a new account. You can now log in."));
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}


// log in
void InitialWindow::on_loginSignInBtn_clicked()
{
    QString username = ui->loginUsernameInput->text();
    QString password = ui->loginPasswdInput->text();

    auto result = loginService->signIn(username, password);

    if(!result.first)
    {
        ui->loginInfoLabel->setText(result.second);
        return;
    }

    emit loggedIn();
}
