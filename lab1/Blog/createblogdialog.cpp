#include "createblogdialog.h"
#include "ui_createblogdialog.h"

CreateBlogDialog::CreateBlogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateBlogDialog)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->setupUi(this);
    ui->okBtn->setEnabled(false);
}

CreateBlogDialog::~CreateBlogDialog()
{
    delete ui;
}

void CreateBlogDialog::setErrorMessage(QString message)
{
    this->ui->errorLabel->setText(message);
}

void CreateBlogDialog::clearWindow()
{
    ui->errorLabel->clear();
    ui->titleInput->clear();
}

void CreateBlogDialog::keyPressEvent(QKeyEvent * event)
{
    // do not close dialog when Escape is clicked
    if(event->key() == Qt::Key::Key_Escape)
        return;

    return QDialog::keyPressEvent(event);
}

void CreateBlogDialog::on_titleInput_textChanged(const QString &text)
{
    if(text.isEmpty())
        return ui->okBtn->setEnabled(false);

    ui->okBtn->setEnabled(true);
}

void CreateBlogDialog::on_okBtn_clicked()
{
    QString title = ui->titleInput->text();
    emit accepted_create_dialog(title);
}
