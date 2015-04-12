#include "db_service.h"

DbService* DbService::_instance = 0;

DbService::DbService() :
    _defaultDatabaseFilename("db.sqlite"),
    _currentUser(new User())
{
    _db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    _db->setDatabaseName(_defaultDatabaseFilename);

    if (!_db->open())
        qDebug() << "Can't open database.";

    if (!isCorrectVersion())
        createDatabase();
}

QString DbService::getCurrentUserType() const
{
    return _currentUser->getUsertype();
}

QString DbService::getCurrentDataBasePath() const
{
    return _db->databaseName();
}

QString DbService::getLastError() const
{
    return _db->lastError().text();
}

bool DbService::testDatabaseConnection() const
{
    if (!_db->isOpen())
        _db->open();

    return _db->isOpen();
}

QSqlDatabase DbService::getCurrentDatabase() const
{
    return _db->database();
}

bool DbService::connectToAnotherDatabase(QString filename)
{
    if (!QFile(filename).exists()) {
        qDebug() << "Wrong file name.";
        return false;
    }

    if (_db->isOpen())
        _db->close();

    _db->setDatabaseName(filename);

    if (!_db->open())
        return false;   

    if (!isCorrectVersion())
        return false;

    return true;
}

bool DbService::isCorrectVersion() const
{
    QStringList tablesList;
    tablesList.append(QString("DRT_USERS"));

    QStringList databaseTablesList = _db->tables();

    for (auto table : tablesList)
        if (!databaseTablesList.contains(table))
        {
            qDebug() << "Incompatible version of the database.";
            return false;
        }

    return true;
}

QStringList DbService::getAllUsers() const
{
    QStringList usersList;
    QSqlQuery query("SELECT USERNAME FROM DRT_USERS");
    int fieldNumber = query.record().indexOf("USERNAME");
    while (query.next())
       usersList.append(query.value(fieldNumber).toString());

    return usersList;
}

bool DbService::loginAs(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT USER_USERNAME, USER_PASSWORD, USER_TYPE FROM DRT_USERS WHERE USERNAME = :username");
    query.bindValue(0, username);
    query.exec();

    if (!query.first())
        return false;

    if (query.value("password").toString() == password)
    {
        User *user = new User(query.value("USER_USERNAME").toString(), query.value("USER_TYPE").toInt());
        _currentUser = user;
        return true;
    }

    return false;
}

void DbService::createDatabase() const
{
    removeCurrentFile();
    _db->open();
    createUsersTable();
}

void DbService::removeCurrentFile() const
{
    QFile oldFile(_defaultDatabaseFilename);

    int i = 0;
    while (QFile(_defaultDatabaseFilename + QString("%1").arg(i)).exists())
        i++;

    oldFile.setFileName(_defaultDatabaseFilename + QString("%1").arg(i));
}

void DbService::createUsersTypesTable() const
{
    QSqlQuery query;
    query.exec("CREATE TABLE DRT_USER_TYPES("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "NAME VARCHAR(50) NOT NULL UNIQUE);");
    query.exec("INSERT INTO DRT_USER_TYPES (ID, NAME) VALUES (0, 'Администратор');");
    query.exec("INSERT INTO DRT_USER_TYPES (ID, NAME) VALUES (1, 'Секретарь');");
    query.exec("INSERT INTO DRT_USER_TYPES (ID, NAME) VALUES (2, 'Работник кафедры');");
}

void DbService::createUsersTable() const
{
    createUsersTypesTable();

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_USERS("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "USER_USERNAME VARCHAR(20) NOT NULL UNIQUE, "
               "USER_PASSWORD VARCHAR(20) NOT NULL, "
               "USER_TYPE INTEGER, "
               "FOREIGN KEY(USER_TYPE_ID) REFERENCES DRT_USER_TYPES(ID),);");
    query.exec("INSERT INTO DRT_USERS (USERNAME, PASSWORD, TYPE) VALUES('admin', 'admin', 0);");
    query.exec("INSERT INTO DRT_USERS (USERNAME, PASSWORD, TYPE) VALUES('secretary', '123', 1);");
    query.exec("INSERT INTO DRT_USERS (USERNAME, PASSWORD, TYPE) VALUES('worker', '123', 2);");
}
