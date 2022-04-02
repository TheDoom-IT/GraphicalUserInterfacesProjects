#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <optional>
#include "../models/user.h"

class UserRepository
{
    Q_DECLARE_TR_FUNCTIONS(LoginService)

    static const QString EMAIL_INDEX;
public:
    UserRepository(QString dataPath, QString usersDir);
    ~UserRepository();

    std::optional<User> findOne(QString userId) const;
    std::optional<User> findOneByEmail(QString email) const;
    std::pair<bool, QString> insertOne(QString userId, QString email, QString password) const;

private:
    QDir dataDir;
    QDir indexDir;

    bool prepareIndexDir(QString dataPath, QString usersDir);
    bool prepareDataDir(QString dataPath, QString usersDir);
    std::pair<bool, QString> writeUserFile(QString userId, QString email, QString password) const;
    std::pair<bool, QString> writeEmailIndexFile(QString email, QString userId) const;

    void throwUnableToAccessData() const;
};

#endif // USERREPOSITORY_H
