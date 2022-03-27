#include "user.h"

bool User::read(const QJsonObject &json)
{
    if(!json.contains("userId") || !json.contains("email") || !json.contains("password"))
        return false;

    if(!json["userId"].isString() || !json["email"].isString() || !json["password"].isString())
        return false;

    this->userId = json["userId"].toString();
    this->email = json["email"].toString();
    this->password = json["password"].toString();

    return true;
}

User::User(QString userId, QString email, QString password)
{
    this->userId = userId;
    this->email = email;
    this->password = password;
}

User::User() : User("", "", "") {}

void User::write(QJsonObject &json) const
{
    json["userId"] = this->userId;
    json["email"] = this->email;
    json["password"] = this->password;
}

