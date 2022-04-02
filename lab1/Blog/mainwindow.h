#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "initialwindow.h"
#include "createblogdialog.h"
#include "repositories/userrepository.h"
#include "repositories/blogrepository.h"
#include "services/loginservice.h"
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

    // data directories
    static const QString DATA_PATH;
    static const QString USERS_DIR;
    static const QString BLOGS_DIR;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show();

private slots:
    // action slots
    void on_actionRemove_triggered();
    void on_actionHome_triggered();
    void on_actionEdit_triggered();
    void on_actionNew_triggered();
    void on_actionLog_out_triggered();
    void on_actionAbout_triggered();

    void on_mainBlogEntryTable_doubleClicked(const QModelIndex &index);

    void on_editSaveBtn_clicked();

    //custom slots
    void enableActions(int);

    void initializeMainWindow();

    void createEmptyBlog(QString title);

    void enableEditRemoveActions();

    void editCreateInputChanged();

    void on_editBackBtn_clicked();

private:
    Ui::MainWindow *ui;

    InitialWindow* initial;
    CreateBlogDialog* createBlogDialog;
    LoginService* loginService;
    BlogService* blogService;
    UserRepository* userRepository;
    BlogRepository* blogRepository;

    // needed for EDIT_CREATE Page
    int selectedEntryIndex;
    bool isNew;

    void showBlogData();
    void resetWindow();

    void clearEditCreatePage();
    void clearShowPage();
    void clearMainPage();
};
#endif // MAINWINDOW_H
