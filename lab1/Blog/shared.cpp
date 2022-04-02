#include "shared.h"

void showInfoDialog(QString title, QString text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}
