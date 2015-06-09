#include "user.h"

User::User():
    _userrole(USER_ROLE_UNDEFINED)
{
}

User::User(QString userName, QString password, int userrole) :
    _userName(userName)
  , _password(password)
{
    setUserrole(userrole);
}

QString User::getUsername() const
{
    return _userName;
}

QString User::getPassword() const
{
    return _password;
}

QString User::getUserroleAsString() const
{
    return userroleTypeToUserroleString(_userrole);
}

User::Userrole User::getUserrole() const
{
    return _userrole;
}

void User::setUsername(const QString& username)
{
    _userName = username;
}

void User::setPassword(const QString& password)
{
    _password = password;
}

void User::setUserrole(const int& userrole)
{
    _userrole = static_cast<Userrole>(userrole);
}

void User::setUserrole(const QString &userrole)
{
    _userrole = userroleStringToUserroleType(userrole);
}

User::Userrole User::userroleStringToUserroleType(const QString& userrole)
{
    if (userrole == "USER_ROLE_UNDEFINED")
        return USER_ROLE_UNDEFINED;
    else if (userrole == "Администратор")
        return ADMINISTRATOR;
    else if (userrole == "Серетарь кафедры")
        return SECRETARY;
    else if (userrole == "Заведующий кафедрой")
        return MANAGER;
    else
        return USER_ROLE_UNDEFINED;
}

QString User::userroleTypeToUserroleString(const User::Userrole userrole)
{
    switch(userrole){
    case USER_ROLE_UNDEFINED:
        return QString("USER_ROLE_UNDEFINED");
        break;
    case ADMINISTRATOR:
        return QString("Администратор");
        break;
    case SECRETARY:
        return QString("Серетарь кафедры");
        break;
    case MANAGER:
        return QString("Заведующий кафедрой");
        break;
    default:
        return QString("USER_ROLE_UNDEFINED");
    }
}
