#ifndef LOGIN_H
#define LOGIN_H

#include "QCoreApplication"
#include "models/user.h"
#include "repositories/userrepository.h"

class LoginService
{
    Q_DECLARE_TR_FUNCTIONS(LoginService)

public:
    LoginService(UserRepository*);
    ~LoginService();

    bool loggedIn();

    std::pair<bool, QString> signUp(QString username, QString email, QString password, QString confPassword) const;
    std::pair<bool, QString> signIn(QString username, QString password);
    bool logOut();

    User* getCurrentUser() const {
        return currentUser;
    }
private:
    User* currentUser;
    UserRepository* userRepository;
};
#endif // LOGIN_H
