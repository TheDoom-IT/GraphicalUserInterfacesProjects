#ifndef CREATEBLOGDIALOG_H
#define CREATEBLOGDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include "services/blogservice.h"
#include "services/loginservice.h"

namespace Ui {
class CreateBlogDialog;
}

class CreateBlogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateBlogDialog(QWidget *parent);
    ~CreateBlogDialog();
    void setErrorMessage(QString message);

    void clearWindow();
private slots:

    void on_titleInput_textChanged(const QString &arg1);

    void on_okBtn_clicked();

signals:
    void accepted(QString title);

private:
    Ui::CreateBlogDialog *ui;

    void keyPressEvent(QKeyEvent *);
};

#endif // CREATEBLOGDIALOG_H
