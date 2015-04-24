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
    return userRoleTypeToUserRoleString(_userRole);
}

User::UserRole User::getUserRole() const
{
    return _userRole;
}

void User::setUserRole(int userRole)
{
    _userRole = static_cast<UserRole>(userRole);
}

User::UserRole User::userRoleStringToUserRoleType(const QString& userrole)
{
    if (userrole == "USER_ROLE_UNDEFINED")
        return USER_ROLE_UNDEFINED;
    else if (userrole == "Администратор")
        return ADMINISTRATOR;
    else if (userrole == "Работник кафедры")
        return WORKER;
    else if (userrole == "Секретарь")
        return SECRETARY;
    else
        return USER_ROLE_UNDEFINED;
}

QString User::userRoleTypeToUserRoleString(User::UserRole userrole)
{
    switch(userrole){
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
