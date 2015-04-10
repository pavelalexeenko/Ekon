#include "db_service.h"

DbService* DbService::_instance = 0;

DbService::DbService() :
    _currentUser(new User())
{
    _db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    _db->setDatabaseName("db.sqlite");
    createDatabase();
}

bool DbService::createDatabase() const
{
    if (!_db->open()) {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    createUsersTable();

    return true;
}

QStringList DbService::getAllUsers() const
{
    QStringList usersList;
    QSqlQuery query("SELECT username FROM users");
    int fieldNumber = query.record().indexOf("username");
    while (query.next())
       usersList.append(query.value(fieldNumber).toString());

    return usersList;
}

QString DbService::getCurrentUserType() const
{
    return _currentUser->getUsertype();
}

bool DbService::isOpen() const
{
    return _db->isOpen();
}

bool DbService::connectToAnotherDatabase(QString fileName)
{
    if (_db->isOpen())
        _db->close();

    _db->setDatabaseName(fileName);

    if (!_db->open()) {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    return true;
}

QString DbService::getCurrentDataBasePath() const
{
    return _db->databaseName();
}

bool DbService::loginAs(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT password, type FROM users WHERE username = :username");
    query.bindValue(0, username);
    query.exec();

    if (!query.first())
        return false;

    if (query.value("password").toString() == password)
    {
        _currentUser->setUserType(query.value("type").toInt());
        return true;
    }

    return false;
}

void DbService::createUsersTable() const
{
    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS users");

    query.exec("create table users ("
               "id int primary key, "
               "username varchar(20) unique, "
               "password varchar(20), "
               "type integer);");
    query.exec("insert into users values(0, 'admin', 'admin', 1);");
    query.exec("insert into users values(1, 'Секретарь', '123', 2);");
    query.exec("insert into users values(2, 'Работник кафедры', '123', 3);");

}
