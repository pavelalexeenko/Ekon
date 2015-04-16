#include "db_service.h"

DbService* DbService::_instance = 0;

DbService::DbService() :
    _defaultDatabaseFilename("db.sqlite"),
    _currentUser(new User())
{
    _db.reset(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")));
    _db->setDatabaseName(_defaultDatabaseFilename);

    if (!_db->open())
        qDebug() << "Can't open database.";

    if (!isCorrectVersion())
        createDatabase();
}

QSharedPointer<User> DbService::getCurrentUser() const
{
    return _currentUser;
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
    if (!QFile(filename).exists())
        throw QString("Wrong file name.");

    if (_db->isOpen())
        _db->close();

    QString oldDatabaseName = _db->databaseName();
    _db->setDatabaseName(filename);

    if (!_db->open())
    {
        _db->setDatabaseName(oldDatabaseName);
        _db->open();
        throw QString("Can't open database");
    }

    if (!isCorrectVersion())
    {
        _db->setDatabaseName(oldDatabaseName);
        _db->open();
        throw QString("Unsupported version of database.");
    }

    return true;
}

bool DbService::isCorrectVersion() const
{
    QStringList tablesList;
    tablesList.append(QString("DRT_USERS"));
    tablesList.append(QString("DRT_USER_TYPES"));
    tablesList.append(QString("DRT_DISCIPLINES"));
    tablesList.append(QString("DRT_TEACHERS"));
    tablesList.append(QString("DRT_GROUPS"));

    QStringList databaseTablesList = _db->tables();

    qDebug() << "Checking database version...";
    for (auto table : tablesList)
        if (!databaseTablesList.contains(table))
        {
            qDebug() << "Incompatible version of the database.";
            return false;
        }

    qDebug() << "Database version is correct.";
    return true;
}

QStringList DbService::getAllUsers() const
{
    QStringList usersList;
    QSqlQuery query("SELECT USER_USERNAME FROM DRT_USERS");
    int fieldNumber = query.record().indexOf("USER_USERNAME");
    while (query.next())
       usersList.append(query.value(fieldNumber).toString());

    return usersList;
}

bool DbService::loginAs(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT USER_USERNAME, USER_PASSWORD, USER_TYPE_ID FROM DRT_USERS WHERE USER_USERNAME = :username");
    query.bindValue(0, username);
    query.exec();

    if (!query.first())
        return false;

    if (query.value("USER_PASSWORD").toString() == password)
    {
        User *user = new User(query.value("USER_USERNAME").toString(), query.value("USER_TYPE_ID").toInt());
        _currentUser.reset(user);
        return true;
    }

    return false;
}

void DbService::createDatabase() const
{
    qDebug() << "Creating database.";
    removeCurrentFile();
    _db->open();
    createUsersTypesTable();
    createUsersTable();
    createDisciplinesTable();
    createTeachersTable();
    createGroupsTable();
}

void DbService::removeCurrentFile() const
{
    qDebug() << "Removing current file.";

    _db->close();
    QFile oldFile(_defaultDatabaseFilename);

    int i = 0;
    while (QFile(_defaultDatabaseFilename + QString("%1").arg(i)).exists())
        i++;

    oldFile.setFileName(_defaultDatabaseFilename + QString("%1").arg(i));
}

void DbService::createUsersTypesTable() const
{
    qDebug() << "Creating users types table.";

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_USER_TYPES("
               "UST_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "UST_NAME VARCHAR(50) NOT NULL UNIQUE);");
    query.exec("INSERT INTO DRT_USER_TYPES (UST_ID, UST_NAME) VALUES (0, 'Администратор');");
    query.exec("INSERT INTO DRT_USER_TYPES (UST_ID, UST_NAME) VALUES (1, 'Секретарь');");
    query.exec("INSERT INTO DRT_USER_TYPES (UST_ID, UST_NAME) VALUES (2, 'Работник кафедры');");
}

void DbService::createUsersTable() const
{
    qDebug() << "Creating users table.";

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_USERS("
               "USER_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "USER_USERNAME VARCHAR(20) NOT NULL UNIQUE, "
               "USER_PASSWORD VARCHAR(20) NOT NULL, "
               "USER_TYPE_ID INTEGER, "
               "FOREIGN KEY(USER_TYPE_ID) REFERENCES DRT_USER_TYPES(UST_ID));");
    query.exec("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) VALUES('admin', '123', 0);");
    query.exec("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) VALUES('secretary', '123', 1);");
    query.exec("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) VALUES('worker', '123', 2);");
}

void DbService::createDisciplinesTable() const
{
    qDebug() << "Creating disciplines table.";

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_DISCIPLINES("
               "DSC_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "DSC_NAME VARCHAR(100) NOT NULL UNIQUE, "
               "DSC_LECTURES DOUBLE NOT NULL, "
               "DSC_PRACTICE INTEGER);");
    query.exec("INSERT INTO DRT_DISCIPLINES (DSC_NAME, DSC_LECTURES, DSC_PRACTICE) VALUES('SPO', 16, 32);");
    query.exec("INSERT INTO DRT_DISCIPLINES (DSC_NAME, DSC_LECTURES, DSC_PRACTICE) VALUES('OPIYP', 32, 64);");
    query.exec("INSERT INTO DRT_DISCIPLINES (DSC_NAME, DSC_LECTURES, DSC_PRACTICE) VALUES('GIMS', '64', 16);");
}

void DbService::createTeachersTable() const
{
    qDebug() << "Creating teachers table.";

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_TEACHERS("
               "TCH_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "TCH_NAME VARCHAR(100) NOT NULL, "
               "TCH_RATE DOUBLE NOT NULL, "
               "TCH_INFO INTEGER);");
    query.exec("INSERT INTO DRT_TEACHERS (TCH_NAME, TCH_RATE, TCH_INFO) VALUES('Хвещук В.И.', 1, 'Профессор');");
    query.exec("INSERT INTO DRT_TEACHERS (TCH_NAME, TCH_RATE, TCH_INFO) VALUES('Головко В.А.', 1, 'Профессор, зав. кафедры');");
    query.exec("INSERT INTO DRT_TEACHERS (TCH_NAME, TCH_RATE, TCH_INFO) VALUES('Давидюк Ю.И.', '0.5', 'Аспирант');");
}

void DbService::createGroupsTable() const
{
    qDebug() << "Creating groups table.";

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_GROUPS("
               "GRP_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "GRP_NAME VARCHAR(100) NOT NULL, "
               "GRP_NUMBER_OF_STUDENTS INTEGER NOT NULL, "
               "GRP_COURSE INTEGER NOT NULL);");
    query.exec("INSERT INTO DRT_GROUPS (GRP_NAME, GRP_NUMBER_OF_STUDENTS, GRP_COURSE) VALUES('АС-33', 19, 5);");
    query.exec("INSERT INTO DRT_GROUPS (GRP_NAME, GRP_NUMBER_OF_STUDENTS, GRP_COURSE) VALUES('АС-32', 20, 5);");
    query.exec("INSERT INTO DRT_GROUPS (GRP_NAME, GRP_NUMBER_OF_STUDENTS, GRP_COURSE) VALUES('АС-34', 25, 4);");
}
