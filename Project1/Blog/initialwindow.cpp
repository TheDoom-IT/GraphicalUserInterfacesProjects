#include "initialwindow.h"
#include "ui_initialwindow.h"

InitialWindow::InitialWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitialWindow)
{
    ui->setupUi(this);

    //Setup Log In Window
    login = new LogInWindow(this);
    connect(ui->loginBtn, SIGNAL(clicked(bool)), login, SLOT(show()));
}

InitialWindow::~InitialWindow()
{
    delete ui;
}
