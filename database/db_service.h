#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <./database/user.h>

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QDir>

#include <QStringList>

#include <QDebug>

class DbService
{
    DbService();
    DbService(const DbService&);
    DbService& operator=(const DbService&);
    ~DbService();

    static DbService* _instance;

public:
    static DbService* getInstance()
    {
        if (!_instance)
            _instance = new DbService();

        return _instance;
    }

public:
    bool createDatabase() const;
    QStringList getAllUsers() const;
    QString getCurrentUserType() const;
    bool isOpen() const;
    bool connectToAnotherDatabase(QString fileName);
    QString getCurrentDataBasePath() const;

    bool loginAs(QString username, QString password);

private:
    void createUsersTable() const;

private:
    User *_currentUser;
    QSqlDatabase *_db;

};

#endif // DBSERVICE_H


