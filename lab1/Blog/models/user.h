#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>

class User
{
public:
    User();
    User(QString userId, QString email, QString password);

    QString getUserId() const {
        return userId;
    }
    bool checkPassword(QString passwd) const {
        return password == passwd;
    }

    void write(QJsonObject&) const;
    bool read(const QJsonObject&);
private:
    QString userId;
    QString email;
    QString password;
};

#endif // USER_H
