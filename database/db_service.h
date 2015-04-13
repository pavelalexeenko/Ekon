#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <./database/user.h>

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
    QSqlDatabase getCurrentDatabase() const;
    QStringList getAllUsers() const;
    QString getCurrentUserType() const;
    QString getCurrentDataBasePath() const;
    QString getLastError() const;

    bool connectToAnotherDatabase(QString filename);
    bool loginAs(QString username, QString password);
    bool testDatabaseConnection() const;

private:
    bool isCorrectVersion() const;

    void createDatabase() const;
    void removeCurrentFile() const;

    void createUsersTypesTable() const;
    void createUsersTable() const;

private:
    const QString _defaultDatabaseFilename;
    User *_currentUser;
    QSqlDatabase *_db;

};

#endif // DBSERVICE_H


