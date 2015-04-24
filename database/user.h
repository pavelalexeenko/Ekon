#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    enum UserRole
    {
        USER_ROLE_UNDEFINED = -1,
        ADMINISTRATOR = 0,
        SECRETARY = 1,
        WORKER = 2
    };
    User();
    User(QString userName, int userRole);

    QString getUserName() const;
    QString getUserRoleAsString() const;
    UserRole getUserRole() const;
    void setUserName(QString userName);
    void setUserRole(int userRole);

    static UserRole userRoleStringToUserRoleType(const QString& userrole);
    static QString userRoleTypeToUserRoleString(UserRole userrole);

private:
    QString _userName;
    UserRole _userRole;
};

#endif // USER_H
