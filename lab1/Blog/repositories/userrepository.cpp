#include "userrepository.h"
#include <qdir.h>
#include <qjsondocument.h>

const QString UserRepository::EMAIL_INDEX = "email.json";

UserRepository::UserRepository(QString dataPath, QString usersDir)
{
    if (!prepareDataDir(dataPath, usersDir) || !prepareIndexDir(dataPath, usersDir))
    {
        throwUnableToAccessData();
    }
}

UserRepository::~UserRepository()
{

}

std::optional<User> UserRepository::findOne(QString userId) const
{
    QFile userFile = QFile(dataDir.filePath(userId + ".json"));
    // if file doesnt exit then there is no such a user
    if(!userFile.exists())
    {
        return std::nullopt;
    }

    // cannot open file
    if (!userFile.open(QIODevice::ReadOnly))
    {
        throwUnableToAccessData();
    }

    QByteArray data = userFile.readAll();

    QJsonDocument jsonData = QJsonDocument::fromJson(data);

    User user;
    if(user.read(jsonData.object()))
        return user;

    return std::nullopt;
}

std::optional<User> UserRepository::findOneByEmail(QString email) const
{
    QFile emailIndex = QFile(indexDir.filePath(EMAIL_INDEX));
    if(!emailIndex.exists())
        // exit program, cannot access data
        throwUnableToAccessData();

    if (!emailIndex.open(QIODevice::ReadOnly))
        // exit program, cannot access data
        throwUnableToAccessData();

    QByteArray data = emailIndex.readAll();
    QJsonDocument jsonData = QJsonDocument::fromJson(data);
    QJsonObject json = jsonData.object();

    if(!json.contains(email) || !json[email].isString())
        return std::nullopt;

    return findOne(json[email].toString());
}

std::pair<bool, QString> UserRepository::insertOne(QString userId, QString email, QString password) const
{
    //check if email is already taken
    auto emailUser = findOneByEmail(email);
    if(emailUser.has_value())
    {
        return std::pair(false, tr("Given email address is already in use."));
    }

    auto userResult = writeUserFile(userId, email, password);
    if(!userResult.first)
        return userResult;

    auto emailResult = writeEmailIndexFile(email, userId);
    if(!emailResult.first)
        return emailResult;

    return std::pair(true, "");
}

bool UserRepository::prepareIndexDir(QString dataPath, QString usersDir)
{
    this->indexDir = QDir(dataPath);
    if(!indexDir.exists() && !indexDir.mkpath("."))
        return false;

    //create and cd to the user directory
    if(!indexDir.cd(usersDir) && !indexDir.mkdir(usersDir) && !indexDir.cd(usersDir))
        return false;


    //create and cd to the index directory
    QString indexDirName = "index";
    if(!indexDir.cd(indexDirName))
    {
        if(!indexDir.mkdir(indexDirName) || !indexDir.cd(indexDirName))
            return false;
    }

    //create email index
    QFile emailIndexFile = QFile(indexDir.filePath(EMAIL_INDEX));

    if(emailIndexFile.exists())
        return true;

    if(!emailIndexFile.open(QIODevice::WriteOnly))
        return false;

    QJsonObject emptyJson;

    emailIndexFile.write(QJsonDocument(emptyJson).toJson());

    return true;
}

bool UserRepository::prepareDataDir(QString dataPath, QString usersDir)
{
    this->dataDir = QDir(dataPath);
    //create data directory
    if(!dataDir.exists() && !dataDir.mkpath("."))
        return false;

    //create and cd to user directory
    if(!dataDir.cd(usersDir))
    {
        if (!dataDir.mkdir(usersDir) || !dataDir.cd(usersDir))
            return false;
    }

    return true;
}

std::pair<bool, QString> UserRepository::writeUserFile(QString userId, QString email, QString password) const
{
    QFile userFile = QFile(dataDir.filePath(userId + ".json"));
    if(userFile.exists())
    {
        return std::pair(false, tr("User with given ID already exists."));
    }


    if(!userFile.open(QIODevice::WriteOnly))
    {
        // program should exit, cannot access data
        throwUnableToAccessData();
    }

    QJsonObject json;
    User user(userId, email, password);
    user.write(json);

    userFile.write(QJsonDocument(json).toJson());

    return std::pair(true, "");
}

std::pair<bool, QString> UserRepository::writeEmailIndexFile(QString email, QString userId) const
{
    QFile emailFile = QFile(indexDir.filePath(EMAIL_INDEX));
    if(!emailFile.exists())
    {
        //hould exit program, cannot access data
        throwUnableToAccessData();
    }

    if(!emailFile.open(QIODevice::ReadOnly))
    {
        // program should exit, cannot access data
        throwUnableToAccessData();
    }

    QByteArray data = emailFile.readAll();
    emailFile.close();

    QJsonDocument jsonData = QJsonDocument::fromJson(data);
    QJsonObject json = jsonData.object();

    json[email] = userId;

    // write to the file
    if(!emailFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        throwUnableToAccessData();
    }

    emailFile.write(QJsonDocument(json).toJson());
    return std::pair(true, "");
}

void UserRepository::throwUnableToAccessData() const
{
    throw std::runtime_error(tr("Unable to access data directory.").toStdString());
}
