#ifndef BLOG_H
#define BLOG_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include "blogentry.h"

class Blog
{
public:
    Blog();
    Blog(QString title, QString ownerId, QList<BlogEntry> items);

    void write(QJsonObject&) const;
    bool read(const QJsonObject&);

    void addEntry(BlogEntry&);
    void removeEntry(unsigned index);

    QString getOwnerId() const {
        return ownerId;
    }

private:
    QString title;
    QString ownerId;
    QList<BlogEntry> items;
};

#endif // BLOG_H
