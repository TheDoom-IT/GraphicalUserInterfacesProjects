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
public:
    UserRepository(QString dataPath, QString usersDir);
    ~UserRepository();

    std::optional<User> findOne(QString userId) const;
    std::pair<bool, QString> insertOne(QString userId, QString email, QString password) const;

private:
    QDir dataDir;
};

#endif // USERREPOSITORY_H
