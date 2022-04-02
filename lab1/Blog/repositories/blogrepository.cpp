#include <QJsonDocument>
#include "blogrepository.h"

const QString BlogRepository::OWNER_ID_INDEX = "ownerId.json";

BlogRepository::BlogRepository(QString dataPath, QString blogsDir)
{
    if (!prepareDataDir(dataPath, blogsDir) || !prepareIndexDir(dataPath, blogsDir))
    {
        throwUnableToAccessData();
    }
}

BlogRepository::~BlogRepository()
{

}

std::optional<Blog> BlogRepository::findOneByOwner(const QString ownerId) const
{
    QFile ownerIdIndexFile = QFile(indexDir.filePath(OWNER_ID_INDEX));
    if(!ownerIdIndexFile.exists())
    {
        // exit program, cannot access data
        throwUnableToAccessData();
    }

    if (!ownerIdIndexFile.open(QIODevice::ReadOnly))
    {
        // exit program, cannot access data
        throwUnableToAccessData();
    }

    QByteArray data = ownerIdIndexFile.readAll();
    QJsonDocument jsonData = QJsonDocument::fromJson(data);
    QJsonObject json = jsonData.object();

    if(!json.contains(ownerId) || !json[ownerId].isString())
        return std::nullopt;

    return findOne(json[ownerId].toString());
}

std::optional<Blog> BlogRepository::findOne(QString blogId) const
{
    QFile blogFile = QFile(dataDir.filePath(blogId + ".json"));
    // if such a file doesnt exist than the given blog doesnt exist
    if(!blogFile.exists())
    {
        return std::nullopt;
    }

    if (!blogFile.open(QIODevice::ReadOnly))
    {
        // cannot access file
        throwUnableToAccessData();
    }

    QByteArray data = blogFile.readAll();

    QJsonDocument jsonData = QJsonDocument::fromJson(data);

    Blog blog;
    if(blog.read(jsonData.object()))
        return blog;

    return std::nullopt;
}

std::pair<bool, QString> BlogRepository::updateOne(const Blog & blog) const
{

    QFile blogFile = QFile(dataDir.filePath(blog.getTitle() + ".json"));

    if(!blogFile.open(QIODevice::WriteOnly))
    {
        throwUnableToAccessData();
    }

    QJsonObject json;
    blog.write(json);

    blogFile.write(QJsonDocument(json).toJson());
    return std::pair(true, "");
}

bool BlogRepository::prepareIndexDir(QString dataPath, QString blogsDir)
{
    this->indexDir = QDir(dataPath);
    if(!indexDir.exists() && !indexDir.mkpath("."))
        return false;

    //create and cd to the user directory
    if(!indexDir.cd(blogsDir) && !indexDir.mkdir(blogsDir) && !indexDir.cd(blogsDir))
        return false;


    //create and cd to the index directory
    QString indexDirName = "index";
    if(!indexDir.cd(indexDirName))
    {
        if(!indexDir.mkdir(indexDirName) || !indexDir.cd(indexDirName))
            return false;
    }

    //create email index
    QFile ownerIdIndexFile = QFile(indexDir.filePath(OWNER_ID_INDEX));

    if(ownerIdIndexFile.exists())
        return true;

    if(!ownerIdIndexFile.open(QIODevice::WriteOnly))
        return false;

    QJsonObject emptyJson;

    ownerIdIndexFile.write(QJsonDocument(emptyJson).toJson());

    return true;
}

bool BlogRepository::prepareDataDir(QString dataPath, QString blogsDir)
{
    this->dataDir = QDir(dataPath);
    //create data directory
    if(!dataDir.exists() && !dataDir.mkpath("."))
        return false;

    //create and cd to blog directory
    if(!dataDir.cd(blogsDir))
    {
        if (!dataDir.mkdir(blogsDir) || !dataDir.cd(blogsDir))
            return false;
    }

    return true;
}

std::pair<bool, QString> BlogRepository::writeBlogFile(const Blog &blog) const
{
    QFile blogFile = QFile(dataDir.filePath(blog.getTitle() + ".json"));
    if(blogFile.exists())
    {
        return std::pair(false, tr("Cannot create second blog for the current user."));
    }

    if(!blogFile.open(QIODevice::WriteOnly))
    {
        throwUnableToAccessData();
    }

    QJsonObject json;
    blog.write(json);

    blogFile.write(QJsonDocument(json).toJson());
    return std::pair(true, "");
}

std::pair<bool, QString> BlogRepository::writeOwnerIdIndexFile(const Blog & blog) const
{
    QFile ownerIdFile = QFile(indexDir.filePath(OWNER_ID_INDEX));
    if(!ownerIdFile.exists())
    {
        //should exit program, cannot access data
        throwUnableToAccessData();
    }

    if(!ownerIdFile.open(QIODevice::ReadOnly))
    {
        //Should exit program, cannot access data!!!
        throwUnableToAccessData();
    }

    QByteArray data = ownerIdFile.readAll();
    ownerIdFile.close();

    QJsonDocument jsonData = QJsonDocument::fromJson(data);
    QJsonObject json = jsonData.object();

    json[blog.getOwnerId()] = blog.getTitle();

    // write to the file
    if(!ownerIdFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        //Should exit program, cannot access data!!!
        throwUnableToAccessData();
    }

    ownerIdFile.write(QJsonDocument(json).toJson());
    return std::pair(true, "");
}


std::pair<bool, QString> BlogRepository::insertOne(const Blog & blog) const
{
    auto blogResult = writeBlogFile(blog);
    if(!blogResult.first)
        return blogResult;

    auto ownerIdResult = writeOwnerIdIndexFile(blog);
    if(!ownerIdResult.first)
        return ownerIdResult;

    return std::pair(true, "");
}

void BlogRepository::throwUnableToAccessData() const
{
    throw std::runtime_error(tr("Unable to access data directory.").toStdString());
}

