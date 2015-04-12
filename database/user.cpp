#include "user.h"

User::User(QString username, int usertype)
{
    setUserName(username);
    setUserType(usertype);
}

QString User::getUsername() const
{
    return _username;
}

void User::setUserName(QString username)
{
    _username = username;
}

QString User::getUsertype() const
{
    switch(_userType){
    case NONE:
        return QString("NONE");
        break;
    case ADMIN:
        return QString("ADMIN");
        break;
    case WORKER:
        return QString("Работник кафедры");
        break;
    case SECRETARY:
        return QString("Секретарь");
        break;
    default:
        return QString("NONE");
    }
}

void User::setUserType(int userType)
{
    switch(userType){
    case 0:
        _userType = NONE;
        break;
    case 1:
        _userType = ADMIN;
        break;
    case 2:
        _userType = SECRETARY;
        break;
    case 3:
        _userType = WORKER;
        break;
    default:
        _userType = NONE;
    }
}
