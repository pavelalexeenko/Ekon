#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    enum UserType
    {
        NONE = 0,
        ADMIN = 1,
        SECRETARY = 2,
        WORKER = 3
    };
    User():_userType(NONE){}
    User(QString username, int usertype);

    QString getUsername() const;
    QString getUsertype() const;
    void setUserName(QString username);
    void setUserType(int userType);

private:
    QString _username;
    UserType _userType;
};

#endif // USER_H
