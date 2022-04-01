#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

const QString MainWindow::DATA_PATH = "data";
const QString MainWindow::USERS_DIR = "users";
const QString MainWindow::BLOGS_DIR = "blogs";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userRepository = new UserRepository(DATA_PATH, USERS_DIR);
    blogRepository = new BlogRepository(DATA_PATH, BLOGS_DIR);
    loginService = new LoginService(userRepository);
    blogService = new BlogService(blogRepository);
    initial = new InitialWindow(this, loginService);
    createBlogDialog = new CreateBlogDialog(this);

    connect(initial, SIGNAL(loggedIn()), this, SLOT(initializeMainWindow()));
    connect(createBlogDialog, SIGNAL(accepted(QString)), this, SLOT(createEmptyBlog(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete userRepository;
    delete loginService;
    delete initial;
}

// this slot is run by loggedIn signal
void MainWindow::initializeMainWindow()
{
    bool result = this->blogService->loadBlogOfUser(this->loginService->getCurrentUser()->getUserId());

    if(result)
    {
        this->prepareEntryTable();
    }

    ui->label->setText(tr("Hi, ") + loginService->getCurrentUser()->getUserId() + ".");

    this->show();
}

void MainWindow::createEmptyBlog(QString title)
{
    std::pair<bool, QString> result = this->blogService->createEmptyBlog(title, loginService->getCurrentUser()->getUserId());
    if(result.first == true)
    {
        this->createBlogDialog->hide();
        return prepareEntryTable();
    }

    this->createBlogDialog->setErrorMessage(result.second);
}

void MainWindow::prepareEntryTable()
{

}

void MainWindow::show() {
    if (!loginService->loggedIn())
    {
        loginService->signIn("dawid", "password");
        return initializeMainWindow();
        return initial->show();
    }

    // loggedIn
    initial->hide();
    this->QMainWindow::show();
    if(this->blogService->getCurrentBlog() == nullptr)
        this->createBlogDialog->show();
}
