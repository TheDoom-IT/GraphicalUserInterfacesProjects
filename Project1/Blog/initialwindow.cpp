#include "initialwindow.h"
#include "ui_initialwindow.h"

InitialWindow::InitialWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitialWindow)
{
    ui->setupUi(this);
}

InitialWindow::~InitialWindow()
{
    delete ui;
}
