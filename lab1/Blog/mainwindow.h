#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "initialwindow.h"
#include "repositories/userrepository.h"
#include "services/login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

    static const QString DATA_PATH;
    static const QString USERS_DIR;
    static const QString BLOGS_DIR;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show();

public slots:
    void initializeMainWindow();

private:
    Ui::MainWindow *ui;

    InitialWindow* initial;
    LoginService* loginService;
    UserRepository* userRepository;
};
#endif // MAINWINDOW_H
