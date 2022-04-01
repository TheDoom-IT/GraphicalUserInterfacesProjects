#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "initialwindow.h"
#include "createblogdialog.h"
#include "repositories/userrepository.h"
#include "repositories/blogrepository.h"
#include "services/login.h"
#include "services/blogservice.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum class Page {
        MAIN,
        SHOW,
        EDIT_CREATE
    };

    static const QString DATA_PATH;
    static const QString USERS_DIR;
    static const QString BLOGS_DIR;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show();

public slots:
    void initializeMainWindow();
    void createEmptyBlog(QString title);

private slots:
    void on_entryTable_itemSelectionChanged();

    void on_actionRemove_triggered();

    void on_actionHome_triggered();

    void on_actionEdit_triggered();

    void on_actionNew_triggered();

    void enableActions(int);

    void on_entryTable_doubleClicked(const QModelIndex &index);

    void on_editSaveBtn_clicked();

private:
    Ui::MainWindow *ui;

    InitialWindow* initial;
    CreateBlogDialog* createBlogDialog;
    LoginService* loginService;
    BlogService* blogService;
    UserRepository* userRepository;
    BlogRepository* blogRepository;

    int selectedEntryIndex;
    bool isCreate;

    void showBlogData();
};
#endif // MAINWINDOW_H
