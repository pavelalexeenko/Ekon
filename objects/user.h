#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    enum Userrole
    {
        USER_ROLE_UNDEFINED = -1,
        ADMINISTRATOR = 0,
        MANAGER = 1,
        SECRETARY = 2
    };
    User();
    User(QString userName, QString password, int userrole);

    QString getUsername() const;
    QString getPassword() const;
    QString getUserroleAsString() const;
    Userrole getUserrole() const;

    void setUsername(const QString& username);
    void setPassword(const QString& password);
    void setUserrole(const int& userrole);
    void setUserrole(const QString& userrole);

    static Userrole userroleStringToUserroleType(const QString& userrole);
    static QString userroleTypeToUserroleString(const Userrole userrole);

private:
    QString _userName;
    QString _password;
    Userrole _userrole;
};

#endif // USER_H
