#include "initialwindow.h"
#include "ui_initialwindow.h"

InitialWindow::InitialWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitialWindow)
{
    ui->setupUi(this);

    // INITIAL is a default page
    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);

    connect(ui->loginSignInBtn, SIGNAL(clicked(bool)), this, SLOT(signIn()));
    connect(ui->rgsSignUpBtn, SIGNAL(clicked(bool)), this, SLOT(signUp()));
}

InitialWindow::~InitialWindow()
{
    delete ui;
}

void InitialWindow::signIn()
{
    QString username = ui->loginUsernameText->text();
    QString password = ui->loginPasswdText->text();

    // check values

    // set current user

    // move to the main window
}

void InitialWindow::signUp()
{
    QString username = ui->rgsUsernameText->text();
    QString email = ui->rgsEmailText->text();
    QString password = ui->rgsPasswdText->text();
    QString confPassword = ui->rgsConfPasswdText->text();

    // check values

    // create new user

    // show information on the initial window about successful signing up

    ui->stackedWidget->setCurrentIndex((int)Page::INITIAL);
}

void InitialWindow::on_signInBtn_clicked()
{
    ui->loginUsernameText->setText("");
    ui->loginPasswdText->setText("");
    ui->stackedWidget->setCurrentIndex((int)Page::LOGIN);
}

void InitialWindow::on_signUpBtn_clicked()
{
    ui->rgsUsernameText->setText("");
    ui->rgsEmailText->setText("");
    ui->rgsPasswdText->setText("");
    ui->rgsConfPasswdText->setText("");
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
