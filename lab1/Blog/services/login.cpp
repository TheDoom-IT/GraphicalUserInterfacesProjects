#include "login.h"

LoginService::LoginService(UserRepository* userRepository)
{
    this->currentUser = nullptr;
    this->userRepository = userRepository;
}

bool LoginService::loggedIn()
{
    return this->currentUser != nullptr;
}

std::pair<bool, QString> LoginService::signUp(QString username, QString email, QString password, QString confPassword) const
{
    if(username == "" || email == "" || password == "" || confPassword == "")
    {
        return std::pair(false,tr("All of the fields must be filled."));
    }

    if (password != confPassword)
    {
        return std::pair(false, tr("Your password and confirmation password must match."));
    }

    std::pair<bool, QString> result = userRepository->insertOne(username, email, password);

    if(!result.first) {
        return result;
    }

    return std::pair(true, "");
}

std::pair<bool, QString> LoginService::signIn(QString username, QString password)
{
    if(username == "" || password == "")
    {
        return std::pair(false, tr("All of the fields must be filled."));
    }

    std::optional<User> user = userRepository->findOne(username);
    if(user.has_value() && user->checkPassword(password)) {
        currentUser = new User(*user);
        return std::pair(true, "");
    }

    // information about invalid logIn
    return std::pair(false, tr("Invalid username and/or password."));
}

bool LoginService::logOut()
{
    delete currentUser;
    currentUser = nullptr;
    return true;
}
