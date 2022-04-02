#include "blogentry.h"
#include <QtDebug>

bool BlogEntry::read(const QJsonObject &json)
{
    if(!json.contains("title") || !json.contains("datetime") || !json.contains("content"))
        return false;

    if(!json["title"].isString() || !json["datetime"].isString() || !json["content"].isString())
        return false;

    QDateTime tempDatetime = QDateTime::fromString(json["datetime"].toString(), Qt::DateFormat::ISODate);

    if(!tempDatetime.isValid())
        return false;

    this->title = json["title"].toString();
    this->datetime = tempDatetime;
    this->content = json["content"].toString();

    return true;
}

void BlogEntry::write(QJsonObject &json) const
{
    json["title"] = this->title;
    json["datetime"] = this->datetime.toString(Qt::DateFormat::ISODate);
    json["content"] = this->content;
}


BlogEntry::BlogEntry() : BlogEntry("", QDateTime(), "")
{

}

BlogEntry::BlogEntry(QString title, QDateTime datetime, QString content)
{
    this->title = title;
    this->datetime = datetime;
    this->content = content;
}
