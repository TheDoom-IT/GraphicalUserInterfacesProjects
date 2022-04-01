#include "blog.h"
#include <QtDebug>

bool Blog::read(const QJsonObject &json)
{
    if(!json.contains("title") || !json.contains("ownerId") || !json.contains("items"))
        return false;

    if(!json["title"].isString() || !json["ownerId"].isString() || !json["items"].isArray())
        return false;

    this->title = json["title"].toString();
    this->ownerId = json["ownerId"].toString();
    QJsonArray itemsArray = json["items"].toArray();

    BlogEntry entry;
    for (auto item : itemsArray)
    {
        if(!item.isObject())
            return false;
        if(!entry.read(item.toObject()))
            return false;
        this->items.push_back(entry);
    }

    return true;
}

void Blog::addEntry(BlogEntry& entry)
{
    this->items.push_back(entry);
}

void Blog::removeEntry(unsigned index)
{
    if(index < this->items.length())
        this->items.removeAt(index);
}

void Blog::updateEntry(unsigned index, QString title, QString content)
{
    auto entry = this->items.at(index);
    entry.title = title;
    entry.content = content;
    this->items.replace(index, entry);
}

void Blog::write(QJsonObject &json) const
{
    json["title"] = this->title;
    json["ownerId"] = this->ownerId;
    QJsonArray itemsArray;
    QJsonObject entry;

    for (auto item : this->items)
    {
        item.write(entry);
        itemsArray.push_back(entry);
    }
    json["items"] = itemsArray;
}


Blog::Blog() : Blog("", "", QList<BlogEntry>())
{

}

Blog::Blog(QString title, QString ownerId, QList<BlogEntry> items)
{
    this->title = title;
    this->ownerId = ownerId;
    this->items = items;
}
