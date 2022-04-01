#ifndef BLOGENTRY_H
#define BLOGENTRY_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class BlogEntry
{
public:
    BlogEntry();
    BlogEntry(QString title, QDateTime datetime, QString content);

    void write(QJsonObject&) const;
    bool read(const QJsonObject&);

    void logOut();
private:
    QString title;
    QDateTime datetime;
    QString content;
};

#endif // BLOGENTRY_H
