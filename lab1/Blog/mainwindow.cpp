#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

const QString MainWindow::DATA_PATH = "data";
const QString MainWindow::USERS_DIR = "users";
const QString MainWindow::BLOGS_DIR = "blogs";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    selectedEntryIndex = -1;
    isCreate = false;

    userRepository = new UserRepository(DATA_PATH, USERS_DIR);
    blogRepository = new BlogRepository(DATA_PATH, BLOGS_DIR);
    loginService = new LoginService(userRepository);
    blogService = new BlogService(blogRepository);
    initial = new InitialWindow(this, loginService);
    createBlogDialog = new CreateBlogDialog(this);



    connect(initial, SIGNAL(loggedIn()), this, SLOT(initializeMainWindow()));
    connect(createBlogDialog, SIGNAL(accepted(QString)), this, SLOT(createEmptyBlog(QString)));
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(enableActions(int)));
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
    ui->stackedWidget->setCurrentIndex((int)Page::MAIN);

    bool result = this->blogService->loadBlogOfUser(this->loginService->getCurrentUser()->getUserId());

    if(result)
    {
        this->showBlogData();
    }

    this->show();
}

void MainWindow::createEmptyBlog(QString title)
{
    std::pair<bool, QString> result = this->blogService->createEmptyBlog(title, loginService->getCurrentUser()->getUserId());
    if(result.first == true)
    {
        this->createBlogDialog->hide();
        return showBlogData();
    }

    this->createBlogDialog->setErrorMessage(result.second);
}

void MainWindow::showBlogData()
{
    this->ui->entryTable->setRowCount(0);

    this->ui->blogTitle->setText(blogService->getCurrentBlog()->getTitle());

    for (BlogEntry entry : blogService->getCurrentBlog()->getEntries())
    {
        int rowCount = ui->entryTable->rowCount();
        ui->entryTable->insertRow(rowCount);

        QTableWidgetItem* title = new QTableWidgetItem(entry.getTitle());
        ui->entryTable->setItem(rowCount, 0, title);
        QTableWidgetItem* date = new QTableWidgetItem(entry.getDatetime());
        ui->entryTable->setItem(rowCount, 1, date);
    }

}

void MainWindow::enableActions(int pageIndex)
{
    Page page = (Page)pageIndex;

    if(page == Page::MAIN)
    {
        ui->actionHome->setEnabled(false);
        ui->actionNew->setEnabled(true);
        //enable actions depending on the current rows selection
        on_entryTable_itemSelectionChanged();
        return;
    }

    if(page == Page::EDIT_CREATE)
    {
        ui->actionHome->setEnabled(true);
        ui->actionNew->setEnabled(false);
        ui->actionRemove->setEnabled(false);
        ui->actionEdit->setEnabled(false);
        return;
    }

    if(page == Page::SHOW)
    {
        ui->actionHome->setEnabled(true);
        ui->actionNew->setEnabled(false);
        ui->actionRemove->setEnabled(true);
        ui->actionEdit->setEnabled(true);
    }
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

void MainWindow::on_entryTable_itemSelectionChanged()
{
    int selectedRows = this->ui->entryTable->selectionModel()->selectedRows().count();
    qDebug() << "selected" << selectedRows;
    if(selectedRows == 0)
    {
        ui->actionEdit->setEnabled(false);
        ui->actionRemove->setEnabled(false);
        return;
    }

    //remove is active if any row is active
    ui->actionRemove->setEnabled(true);

    if(selectedRows == 1)
    {
        ui->actionEdit->setEnabled(true);
        return;
    }

    //edit is inactive for multiple rows
    ui->actionEdit->setEnabled(false);
}

void MainWindow::on_actionRemove_triggered()
{
    if(ui->stackedWidget->currentIndex() == (int)Page::SHOW)
    {
        QList<int> entries{this->selectedEntryIndex};
        blogService->removeEntries(entries);
        this->showBlogData();

        //move to home
        on_actionHome_triggered();
        return;
    }

    auto rows = ui->entryTable->selectionModel()->selectedRows();
    QList<int> rowsNumber;
    for (auto row : rows)
    {
        rowsNumber.push_back(row.row());
    }

    std::sort(rowsNumber.rbegin(), rowsNumber.rend());
    blogService->removeEntries(rowsNumber);
    this->showBlogData();
}

void MainWindow::on_actionHome_triggered()
{
    this->selectedEntryIndex = -1;
    ui->stackedWidget->setCurrentIndex((int)Page::MAIN);
}

void MainWindow::on_actionEdit_triggered()
{
    if(selectedEntryIndex == -1)
        this->selectedEntryIndex = ui->entryTable->selectionModel()->selectedRows().first().row();

    isCreate = false;
    BlogEntry blogEntry = blogService->getCurrentBlog()->getEntries().at(selectedEntryIndex);
    ui->editTitleText->setText(blogEntry.getTitle());
    ui->editContentText->setText(blogEntry.getContent());
    ui->stackedWidget->setCurrentIndex((int)Page::EDIT_CREATE);
}

void MainWindow::on_actionNew_triggered()
{
    qDebug() << "new entry";
    isCreate = true;
    ui->editTitleText->clear();
    ui->editContentText->clear();
    ui->stackedWidget->setCurrentIndex((int)Page::EDIT_CREATE);
}

void MainWindow::on_entryTable_doubleClicked(const QModelIndex &index)
{
    this->selectedEntryIndex = index.row();
    BlogEntry blogEntry = blogService->getCurrentBlog()->getEntries().at(selectedEntryIndex);
    ui->showTitleLabel->setText(blogEntry.getTitle());
    ui->showDatetimeLabel->setText(blogEntry.getDatetime());
    ui->showContentLabel->setText(blogEntry.getContent());
    ui->stackedWidget->setCurrentIndex((int)Page::SHOW);
}

void MainWindow::on_editSaveBtn_clicked()
{
    QString title = ui->editTitleText->text();
    QString content = ui->editContentText->toPlainText();

    if(isCreate)
    {
        blogService->addEntry(title, content);
    } else
    {
        blogService->updateEntry(selectedEntryIndex, title, content);
    }


    this->showBlogData();
    return on_actionHome_triggered();
}
