#include "userrepository.h"
#include <qdir.h>
#include <qjsondocument.h>

UserRepository::UserRepository(QString dataPath, QString usersDir)
{
    this->dataDir = QDir(dataPath);
    if(!dataDir.exists())
    {
        dataDir.mkpath(".");
    }

    if(!dataDir.cd(usersDir))
    {
        dataDir.mkdir(usersDir);
    }
}

UserRepository::~UserRepository()
{

}

std::optional<User> UserRepository::findOne(QString userId) const
{
    QFile userFile = QFile(dataDir.filePath(userId + ".json"));
    if(!userFile.exists())
    {
        return std::nullopt;
    }

    if (!userFile.open(QIODevice::ReadOnly))
    {
        return std::nullopt;
    }

    QByteArray data = userFile.readAll();

    QJsonDocument jsonData = QJsonDocument::fromJson(data);

    User user;
    if(user.read(jsonData.object()))
        return user;

    return std::nullopt;
}

std::pair<bool, QString> UserRepository::insertOne(QString userId, QString email, QString password) const
{
    QFile userFile = QFile(dataDir.filePath(userId + ".json"));
    if(userFile.exists())
    {
        return std::pair(false, tr("User with given ID already exists."));
    }

    if(!userFile.open(QIODevice::WriteOnly))
    {
        return std::pair(false, tr("Unable to create user."));
    }

    QJsonObject json;
    User user(userId, email, password);
    user.write(json);

    userFile.write(QJsonDocument(json).toJson());
    return std::pair(true, "");
}
