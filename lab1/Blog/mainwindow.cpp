#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shared.h"

// data directories
const QString MainWindow::DATA_PATH = "data";
const QString MainWindow::USERS_DIR = "users";
const QString MainWindow::BLOGS_DIR = "blogs";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->editSaveBtn->setEnabled(false);
    ui->mainBlogEntryTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->mainBlogEntryTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->mainBlogEntryTable->horizontalHeader()->setMinimumSectionSize(ui->mainBlogEntryTable->width()/3.0);
    ui->stackedWidget->setCurrentIndex((int)Page::MAIN);

    // initialize private fields
    userRepository = new UserRepository(DATA_PATH, USERS_DIR);
    blogRepository = new BlogRepository(DATA_PATH, BLOGS_DIR);
    loginService = new LoginService(userRepository);
    blogService = new BlogService(blogRepository);
    initial = new InitialWindow(this, loginService);
    createBlogDialog = new CreateBlogDialog(this);

    // connect
    connect(initial, SIGNAL(loggedIn()), this, SLOT(initializeMainWindow()));
    connect(createBlogDialog, SIGNAL(accepted_create_dialog(QString)), this, SLOT(createEmptyBlog(QString)));
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(enableActions(int)));
    connect(ui->mainBlogEntryTable, SIGNAL(itemSelectionChanged()), this, SLOT(enableEditRemoveActions()));

    connect(ui->editContentInput, SIGNAL(textChanged()), this, SLOT(editCreateInputChanged()));
    connect(ui->editTitleInput, SIGNAL(textChanged(QString)), this, SLOT(editCreateInputChanged()));



    // needed for EDIT_CREATE Page
    // index of entry currently edited/shown
    selectedEntryIndex = -1;
    // should EDIT_CREATE Page create new entry or edit existing one?
    isNew = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete userRepository;
    delete blogRepository;
    delete loginService;
    delete blogService;
    delete initial;
    delete createBlogDialog;
}

void MainWindow::initializeMainWindow()
{
    resetWindow();
    enableActions((int)Page::MAIN);

    this->blogService->loadBlogOfUser(this->loginService->getCurrentUser()->getUserId());
    this->showBlogData();

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
    clearMainPage();

    if(blogService->getCurrentBlog() == nullptr)
        return;

    this->ui->mainBlogTitleLabel->setText(blogService->getCurrentBlog()->getTitle());

    for (BlogEntry entry : blogService->getCurrentBlog()->getEntries())
    {
        int rowCount = ui->mainBlogEntryTable->rowCount();
        ui->mainBlogEntryTable->insertRow(rowCount);

        QTableWidgetItem* title = new QTableWidgetItem(entry.getTitle());
        ui->mainBlogEntryTable->setItem(rowCount, 0, title);
        QTableWidgetItem* date = new QTableWidgetItem(entry.getDatetime());
        date->setTextAlignment(Qt::AlignCenter);
        ui->mainBlogEntryTable->setItem(rowCount, 1, date);
    }

}

void MainWindow::resetWindow()
{
    selectedEntryIndex = -1;
    isNew = false;
    clearEditCreatePage();
    clearShowPage();
    clearMainPage();
    ui->stackedWidget->setCurrentIndex((int)Page::MAIN);
}

void MainWindow::clearEditCreatePage()
{
    ui->editContentInput->clear();
    ui->editTitleInput->clear();
}

void MainWindow::clearShowPage()
{
    ui->showTitleLabel->clear();
    ui->showDatetimeLabel->clear();
    ui->showContentLabel->clear();
}

void MainWindow::clearMainPage()
{
    ui->mainBlogTitleLabel->clear();
    ui->mainBlogEntryTable->setRowCount(0);
}

void MainWindow::enableActions(int pageIndex)
{
    Page page = (Page)pageIndex;

    if(page == Page::MAIN)
    {
        ui->actionHome->setEnabled(false);
        ui->actionNew->setEnabled(true);

        // edit/remove action depends on the current rows selection
        enableEditRemoveActions();
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
        return initial->show();
    }

    // loggedIn
    initial->hide();
    this->QMainWindow::show();
    //create blog if doesn't exist
    if(this->blogService->getCurrentBlog() == nullptr)
    {
        this->createBlogDialog->clearWindow();
        this->createBlogDialog->show();
    }
}

void MainWindow::enableEditRemoveActions()
{
    int selectedRows = this->ui->mainBlogEntryTable->selectionModel()->selectedRows().count();

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

void MainWindow::editCreateInputChanged()
{
    QString title = ui->editTitleInput->text();
    QString content = ui->editContentInput->toPlainText();

    if(title == "" || content == "")
        return ui->editSaveBtn->setEnabled(false);

    ui->editSaveBtn->setEnabled(true);
}

void MainWindow::on_actionRemove_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Do you really want to remove this entry/entries?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret == (int)QMessageBox::No)
    {
        return;
    }

    // remove single entry from the SHOW page
    if(ui->stackedWidget->currentIndex() == (int)Page::SHOW)
    {
        QList<int> entries{this->selectedEntryIndex};
        blogService->removeEntries(entries);
        this->showBlogData();

        //move to home
        ui->actionHome->trigger();
        return;
    }

    // remove multiple entries from the MAIN page
    auto rows = ui->mainBlogEntryTable->selectionModel()->selectedRows();
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

// move to the SHOW page
void MainWindow::on_mainBlogEntryTable_doubleClicked(const QModelIndex &index)
{
    // save which entry is shown
    this->selectedEntryIndex = index.row();

    BlogEntry blogEntry = blogService->getCurrentBlog()->getEntries().at(selectedEntryIndex);
    ui->showTitleLabel->setText(blogEntry.getTitle());
    ui->showDatetimeLabel->setText(blogEntry.getDatetime());
    ui->showContentLabel->setText(blogEntry.getContent());
    ui->stackedWidget->setCurrentIndex((int)Page::SHOW);
}

// move to the EDIT page
void MainWindow::on_actionEdit_triggered()
{
    // selectedEntryIndex should be initialized if edit run from MAIN Page
    // if run from SHOW the selectedEntryIndex is already initialized
    if(ui->stackedWidget->currentIndex() == (int)Page::MAIN)
        this->selectedEntryIndex = ui->mainBlogEntryTable->selectionModel()->selectedRows().first().row();

    isNew = false;
    BlogEntry blogEntry = blogService->getCurrentBlog()->getEntries().at(selectedEntryIndex);
    ui->editTitleInput->setText(blogEntry.getTitle());
    ui->editContentInput->setText(blogEntry.getContent());
    ui->stackedWidget->setCurrentIndex((int)Page::EDIT_CREATE);
}

// move to the NEW page
void MainWindow::on_actionNew_triggered()
{
    isNew = true;
    ui->editTitleInput->clear();
    ui->editContentInput->clear();
    ui->stackedWidget->setCurrentIndex((int)Page::EDIT_CREATE);
}

// save edited/new entry
void MainWindow::on_editSaveBtn_clicked()
{
    QString title = ui->editTitleInput->text();
    QString content = ui->editContentInput->toPlainText();

    std::pair<bool, QString> result;
    if(isNew)
    {
        result = blogService->addEntry(title, content);
    } else
    {
        result = blogService->updateEntry(selectedEntryIndex, title, content);
    }

    if(!result.first)
        showInfoDialog(tr("Error"), tr("Unable to save new entry: ") + result.second);
    else
        this->showBlogData();

    // move to MAIN Page
    return ui->actionHome->trigger();
}

// logOut current user and show InitialWindow
void MainWindow::on_actionLog_out_triggered()
{
    loginService->logOut();
    this->hide();
    initial->resetWindow();
    initial->show();
}

// show about dialog
void MainWindow::on_actionAbout_triggered()
{
    showInfoDialog(tr("About"), tr("Blog desktop application\nEGUI Project 2022L"));
}

void MainWindow::on_editBackBtn_clicked()
{
    // move to MAIN Page
    return ui->actionHome->trigger();
}
