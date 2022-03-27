#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::DATA_PATH = "data";
const QString MainWindow::USERS_DIR = "users";
const QString MainWindow::BLOGS_DIR = "blogs";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userRepository = new UserRepository(DATA_PATH, USERS_DIR);
    loginService = new LoginService(userRepository);
    initial = new InitialWindow(this, loginService);

    connect(initial, SIGNAL(loggedIn()), this, SLOT(initializeMainWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMainWindow()
{
    // TODO: Load data connected with current user

    ui->label->setText(tr("Hi, ") + loginService->getCurrentUser()->getUserId() + ".");


    this->show();
}

void MainWindow::show() {
    if (loginService->loggedIn())
    {
        initial->hide();
        return QMainWindow::show();
    }

    // show login window if not logged in
    initial->show();
}
