#include "user.h"

User::User():
_userRole(USER_ROLE_UNDEFINED)
{
}

User::User(QString userName, int userRole)
{
    setUserName(userName);
    setUserRole(userRole);
}

QString User::getUserName() const
{
    return _userName;
}

void User::setUserName(QString userName)
{
    _userName = userName;
}

QString User::getUserRoleAsString() const
{
    switch(_userRole){
    case USER_ROLE_UNDEFINED:
        return QString("USER_ROLE_UNDEFINED");
        break;
    case ADMINISTRATOR:
        return QString("Администратор");
        break;
    case WORKER:
        return QString("Работник кафедры");
        break;
    case SECRETARY:
        return QString("Секретарь");
        break;
    default:
        return QString("USER_ROLE_UNDEFINED");
    }
}

User::UserRole User::getUserRole() const
{
    return _userRole;
}

void User::setUserRole(int userRole)
{
    _userRole = static_cast<UserRole>(userRole);
  /*  switch(userRole){
    case -1:
        _userRole = USER_ROLE_UNDEFINED;
        break;
    case 0:
        _userRole = ADMINISTRATOR;
        break;
    case 1:
        _userRole = SECRETARY;
        break;
    case 2:
        _userRole = WORKER;
        break;
    default:
        _userRole = USER_ROLE_UNDEFINED;
    }*/
}
