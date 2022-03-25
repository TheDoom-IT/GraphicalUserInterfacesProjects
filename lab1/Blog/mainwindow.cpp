#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initial = new InitialWindow(this);
    initial->show();

    connect(initial, SIGNAL(openMainWindow()), this, SLOT(openMainWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openMainWindow()
{
    initial->hide();
    this->show();
}

