#include <QJsonDocument>
#include "blogrepository.h"

BlogRepository::BlogRepository(QString dataPath, QString blogsDir)
{

    this->dataDir = QDir(dataPath);
    if(!dataDir.exists())
    {
        dataDir.mkpath(".");
    }

    if(!dataDir.cd(blogsDir))
    {
        dataDir.mkdir(blogsDir);
    }
}

std::optional<Blog> BlogRepository::findOneByOwner(const QString ownerId) const
{
    QFile blogFile = QFile(dataDir.filePath(ownerId + ".json"));
    if(!blogFile.exists())
    {
        return std::nullopt;
    }

    if (!blogFile.open(QIODevice::ReadOnly))
    {
        return std::nullopt;
    }

    QByteArray data = blogFile.readAll();

    QJsonDocument jsonData = QJsonDocument::fromJson(data);

    Blog blog;
    if(blog.read(jsonData.object()))
        return blog;

    return std::nullopt;
}

std::optional<Blog> BlogRepository::findOne(QString blogId) const
{
    // TODO: findOne

    return std::nullopt;
}

std::pair<bool, QString> BlogRepository::updateOne(const Blog & blog) const
{

    QFile blogFile = QFile(dataDir.filePath(blog.getOwnerId() + ".json"));

    if(!blogFile.open(QIODevice::WriteOnly))
    {
        return std::pair(false, tr("Unable to update blog."));
    }

    QJsonObject json;
    blog.write(json);

    blogFile.write(QJsonDocument(json).toJson());
    return std::pair(true, "");
}


std::pair<bool, QString> BlogRepository::insertOne(const Blog & blog) const
{
    QFile blogFile = QFile(dataDir.filePath(blog.getOwnerId() + ".json"));
    if(blogFile.exists())
    {
        return std::pair(false, tr("Cannot create second blog for the current user."));
    }

    // TODO: How to check if blog with such an id already exists???

    if(!blogFile.open(QIODevice::WriteOnly))
    {
        return std::pair(false, tr("Unable to create blog."));
    }

    QJsonObject json;
    blog.write(json);

    blogFile.write(QJsonDocument(json).toJson());
    return std::pair(true, "");
}

