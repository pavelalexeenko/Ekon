#include "db_service.h"

DbService* DbService::_instance = 0;

DbService::DbService() :
    _defaultDatabaseFilename("db.sqlite"),
    _currentUser(new User())
{
    qDebug() << __FUNCTION__;

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

bool DbService::addUser(const User& user)
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.prepare("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) "
                  "VALUES (:username, :password, :type)");
    query.bindValue(":username", user.getUsername());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":type", user.getUserrole());
    if (!query.exec())
        return false;

    return true;
}

bool DbService::addTeacher(const Teacher &teacher)
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.prepare("INSERT INTO DRT_TEACHERS (TCH_NAME, TCH_RATE, TCH_INFO) "
                  "VALUES (:name, :rate, :info)");
    query.bindValue(":name", teacher.getName());
    query.bindValue(":rate", teacher.getRate());
    query.bindValue(":info", teacher.getInfo());
    if (!query.exec())
        return false;

    return true;
}

bool DbService::addDiscipline(const Discipline &discipline)
{
    qDebug() << __FUNCTION__;

    QString fields("DSC_NAME,DSC_LECTURES,DSC_LABORATORY,DSC_PRACTICAL,DSC_CONSULTATION,DSC_EXAMINATIONS,DSC_TESTS,DSC_CURRENT_CONSULTATION, "
                   "DSC_INTRODUCTORY_PRACTICE,DSC_PRE_DIPLOMA_PRACTICE,DSC_COURSEWORK,DSC_GUIDED_INDEPENDENT_WORK,DSC_CONTROL_WORK, "
                   "DSC_GRADUATION_DESIGN,DSC_GUIDE_GRADUATE,DSC_STATE_EXAM,DSC_HES,DSC_GUIDE_CHAIR,DSC_UIRS");

    QSqlQuery query;
    query.prepare("INSERT INTO DRT_DISCIPLINES (" + fields + ") "
                  "VALUES (:name, :lec, :lab, :prac, :consult, :exam, :tests, :curCons, :intrPrac, :preDiplPrac, :course, :guIndWork, :contrl, "
                  " :gradDesign, :guGrad, :stateExam, :hes, :guideChair, :uirs)");

    query.bindValue(":name", discipline.getName());
    query.bindValue(":lec", discipline.getLectures());
    query.bindValue(":lab", discipline.getLaboratory());
    query.bindValue(":prac", discipline.getPractical());
    query.bindValue(":consult", discipline.hasConsultation());
    query.bindValue(":exam", discipline.hasExamination());
    query.bindValue(":tests", discipline.hasTests());
    query.bindValue(":curCons", discipline.hasCurrentConsultation());
    query.bindValue(":intrPrac", discipline.hasIntroductoryPractice());
    query.bindValue(":preDiplPrac", discipline.hasPreDiplomaPractice());
    query.bindValue(":course", discipline.hasCourseWork());
    query.bindValue(":guIndWork", discipline.hasGuideIndependentWork());
    query.bindValue(":contrl", discipline.hasControlWork());
    query.bindValue(":gradDesign", discipline.hasGraduationDesign());
    query.bindValue(":guGrad", discipline.hasGuideGraduate());
    query.bindValue(":stateExam", discipline.hasStateExam());
    query.bindValue(":hes", discipline.hasHes());
    query.bindValue(":guideChair", discipline.hasGuideChair());
    query.bindValue(":uirs", discipline.hasUirs());

    if (!query.exec())
        return false;

    return true;
}

bool DbService::addGroup(const Group& group)
{
    qDebug() << __FUNCTION__;

    QString fields("GRP_NAME,GRP_NUMBER_OF_STUDENTS,GRP_COURSE,GRP_NUMBER_OF_SUBGROUPS,GRP_SEMESTR,GRP_FACULTET,GRP_SPECIALITY,GRP_NOTE");

    QSqlQuery query;
    query.prepare("INSERT INTO DRT_GROUPS (" + fields + ") "
                   "VALUES(:name, :students, :course, :subgroups, :semestr, :faculty, :spec, :note);");

    query.bindValue(":name", group.getName());
    query.bindValue(":students", group.getNumberOfStudents());
    query.bindValue(":course", group.getCourse());
    query.bindValue(":subgroups", group.getNumberOfSubgroups());
    query.bindValue(":semestr", group.getSemestr());
    query.bindValue(":faculty", group.getFaculty());
    query.bindValue(":spec", group.getSpeciality());
    query.bindValue(":note", group.getNote());

    if (!query.exec())
        return false;

    return true;
}

bool DbService::addFlow(const Flow &flow)
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.prepare("INSERT INTO DRT_FLOWS (FLW_NAME,FLW_NOTE) VALUES(:name, :note);");

    query.bindValue(":name", flow.getName());
    query.bindValue(":note", flow.getNote());

    if (!query.exec())
        return false;

    int id = query.lastInsertId().toInt();

    for (auto groupId : flow.getGroupIds())
    {
        query.prepare("INSERT INTO DRT_LINKS (LNK_FLW_ID,LNK_GRP_ID) VALUES(:flowId, :groupId);");
        query.bindValue(":flowId", id);
        query.bindValue(":groupId", groupId);

        if (!query.exec())
            return false;
    }

    return true;
}

QString DbService::getFlowNameById(const int &id)
{
    QSqlQuery query;
    query.prepare("SELECT GRP_NAME FROM DRT_GROUPS WHERE GRP_ID = :id");
    query.bindValue(":id", id);
    query.exec();

    if (!query.first())
        throw QString("No group with such id.");

    return query.record().value("GRP_NAME").toString();
}

QList<Group> DbService::getAllGroups() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_GROUPS ORDER BY GRP_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    QList<Group> groups;

    while(query.next())
        groups.append(toGroupObject(query.record()));

    return groups;
}

QList<Flow> DbService::getAllFlows() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_FLOWS ORDER BY FLW_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    if (query.size() < 1)
        return QList<Flow>();

    QList<Flow> flows;

    while(query.next())
        flows.append(toFlowObject(query.record()));

    return flows;
}

Group DbService::toGroupObject(const QSqlRecord& record) const
{
    Group group;
    group.setId(record.value("GRP_ID").toInt());
    group.setName(record.value("GRP_NAME").toString());
    group.setNumberOfStudents(record.value("GRP_NUMBER_OF_STUDENTS").toInt());
    group.setCourse(record.value("GRP_COURSE").toInt());
    group.setNumberOfSubgroups(record.value("GRP_NUMBER_OF_SUBGROUPS").toInt());
    group.setSemestr(record.value("GRP_SEMESTR").toInt());
    group.setFaculty(record.value("GRP_FACULTET").toString());
    group.setSpeciality(record.value("GRP_SPECIALITY").toString());
    group.setNote(record.value("GRP_NOTE").toString());

    return group;
}

Flow DbService::toFlowObject(const QSqlRecord& record) const
{
    Flow flow;
    flow.setId(record.value("FLW_ID").toInt());
    flow.setName(record.value("FLW_NAME").toString());
    flow.setNote(record.value("FLW_NOTE").toString());
    flow.setGroupIds(getGroupsIdsByFlowId(flow.getId()));

    return flow;
}

QSet<int> DbService::getGroupsIdsByFlowId(const int &flowId) const
{
    QSqlQuery query;
    query.prepare("SELECT LNK_GRP_ID FROM DRT_LINKS WHERE LNK_FLW_ID = :flowId");
    query.bindValue(":flowId", flowId);

    if (!query.exec())
        throw QString(query.lastError().text());

    QSet<int> ids;
    while (query.next())
        ids.insert(query.value("LNK_GRP_ID").toInt());

    return ids;
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
    tablesList.append(QString("DRT_FLOWS"));
    tablesList.append(QString("DRT_LINKS"));
    tablesList.append(QString("DRT_LOAD_CALCULATION"));
    tablesList.append(QString("DRT_LOAD_DISTRIBUTION"));

    tablesList.append(QString("VIEW_FLOWS"));
    tablesList.append(QString("VIEW_LOAD_CALCULATION"));

    QStringList databaseTablesList = _db->tables(QSql::AllTables);

    qDebug() << "Checking database version...";
    for (auto table : tablesList)
        if (!databaseTablesList.contains(table))
        {
            qDebug() << "Incompatible version of the database. Missing table - " << table;
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

QStringList DbService::getAllUserroles() const
{
    QStringList usersList;
    QSqlQuery query("SELECT UST_NAME FROM DRT_USER_TYPES");
    int fieldNumber = query.record().indexOf("UST_NAME");
    while (query.next())
        usersList.append(query.value(fieldNumber).toString());

    return usersList;
}

bool DbService::loginAs(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT USER_USERNAME, USER_PASSWORD, USER_TYPE_ID FROM DRT_USERS WHERE USER_USERNAME = :username");
    query.bindValue(":username", username);
    query.exec();

    if (!query.first())
        return false;

    if (query.value("USER_PASSWORD").toString() == password)
    {
        User *user = new User(query.value("USER_USERNAME").toString(),
                              query.value("USER_PASSWORD").toString(),
                              query.value("USER_TYPE_ID").toInt());
        _currentUser.reset(user);
        return true;
    }

    return false;
}

void DbService::createDatabase() const
{
    qDebug() << __FUNCTION__;

    removeCurrentFile();

    QSqlDatabase::database().transaction();
    createUsersTypesTable();
    createUsersTable();
    createDisciplinesTable();
    createTeachersTable();
    createGroupsTable();
    createFlowsTable();
    createLinksTable();
    createFlowsView();
    createLoadCalculation();
    createLoadDistribution();
    createLoadCalculationView();
    QSqlDatabase::database().commit();
}

void DbService::removeCurrentFile() const
{
    qDebug() << __FUNCTION__;

    _db->close();
    QFile oldFile(_defaultDatabaseFilename);

    int i = 0;
    while (QFile(_defaultDatabaseFilename + QString("%1").arg(i)).exists())
        i++;

    oldFile.rename(_defaultDatabaseFilename + QString("%1").arg(i));

    _db->open();
}

void DbService::createUsersTypesTable() const
{
    qDebug() << __FUNCTION__;

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
    qDebug() << __FUNCTION__;

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
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_DISCIPLINES("
               "DSC_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "DSC_NAME VARCHAR(100) NOT NULL UNIQUE, "
               "DSC_LECTURES INTEGER NOT NULL DEFAULT 0, "
               "DSC_LABORATORY INTEGER NOT NULL DEFAULT 0, "
               "DSC_PRACTICAL INTEGER NOT NULL DEFAULT 0, "
               "DSC_CONSULTATION INTEGER NOT NULL DEFAULT 0, "
               "DSC_EXAMINATIONS INTEGER NOT NULL DEFAULT 0, "
               "DSC_TESTS INTEGER NOT NULL DEFAULT 0, "
               "DSC_CURRENT_CONSULTATION INTEGER NOT NULL DEFAULT 0, "
               "DSC_INTRODUCTORY_PRACTICE INTEGER NOT NULL DEFAULT 0, "
               "DSC_PRE_DIPLOMA_PRACTICE INTEGER NOT NULL DEFAULT 0, "
               "DSC_COURSEWORK INTEGER NOT NULL DEFAULT 0, "
               "DSC_GUIDED_INDEPENDENT_WORK INTEGER NOT NULL DEFAULT 0, "
               "DSC_CONTROL_WORK INTEGER NOT NULL DEFAULT 0, "
               "DSC_GRADUATION_DESIGN INTEGER NOT NULL DEFAULT 0, "
               "DSC_GUIDE_GRADUATE INTEGER NOT NULL DEFAULT 0, "
               "DSC_STATE_EXAM INTEGER NOT NULL DEFAULT 0, "
               "DSC_HES INTEGER NOT NULL DEFAULT 0, "
               "DSC_GUIDE_CHAIR INTEGER NOT NULL DEFAULT 0, "
               "DSC_UIRS INTEGER NOT NULL DEFAULT 0 "
               ");");

    QString fields("DSC_NAME,DSC_LECTURES,DSC_LABORATORY,DSC_PRACTICAL,DSC_CONSULTATION,DSC_EXAMINATIONS,DSC_TESTS,DSC_CURRENT_CONSULTATION, "
                   "DSC_INTRODUCTORY_PRACTICE,DSC_PRE_DIPLOMA_PRACTICE,DSC_COURSEWORK,DSC_GUIDED_INDEPENDENT_WORK,DSC_CONTROL_WORK, "
                   "DSC_GRADUATION_DESIGN,DSC_GUIDE_GRADUATE,DSC_STATE_EXAM,DSC_HES,DSC_GUIDE_CHAIR,DSC_UIRS");

    query.exec("INSERT INTO DRT_DISCIPLINES (" + fields + ") VALUES('SPO', 16, 32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);");
    query.exec("INSERT INTO DRT_DISCIPLINES (" + fields + ") VALUES('OPIYP', 32, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);");
    query.exec("INSERT INTO DRT_DISCIPLINES (" + fields + ") VALUES('GIMS', '64', 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);");
}

void DbService::createTeachersTable() const
{
    qDebug() << __FUNCTION__;

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
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_GROUPS("
               "GRP_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "GRP_NAME VARCHAR(100) NOT NULL, "
               "GRP_NUMBER_OF_STUDENTS INTEGER NOT NULL, "
               "GRP_COURSE INTEGER NOT NULL, "
               "GRP_NUMBER_OF_SUBGROUPS INTEGER NOT NULL DEFAULT 1, "
               "GRP_SEMESTR INTEGER NOT NULL, "
               "GRP_FACULTET VARCHAR(100), "
               "GRP_SPECIALITY VARCHAR(100), "
               "GRP_NOTE VARCHAR(200));");

    QString fields("GRP_NAME,GRP_NUMBER_OF_STUDENTS,GRP_COURSE,GRP_NUMBER_OF_SUBGROUPS,GRP_SEMESTR,GRP_FACULTET,GRP_SPECIALITY,GRP_NOTE");

    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-32', 19, 5, 2, 9,'ЭИС','АСОИ','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-33', 20, 5, 2, 9,'ЭИС','АСОИ','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-34', 25, 4, 2, 7,'ЭИС','АСОИ','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-35', 22, 4, 2, 7,'ЭИС','АСОИ','Примечание');");

    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-44', 15, 5, 2, 9,'ЭИС','ЭВМСиС','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-45', 16, 5, 2, 9,'ЭИС','ЭВМСиС','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-46', 22, 4, 2, 7,'ЭИС','ЭВМСиС','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-47', 25, 4, 2, 7,'ЭИС','ЭВМСиС','Примечание');");
}

void DbService::createFlowsTable() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_FLOWS("
               "FLW_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "FLW_NAME VARCHAR(100) NOT NULL, "
               "FLW_NOTE VARCHAR(200));");

    QString fields("FLW_NAME,FLW_NOTE");

    query.exec("INSERT INTO DRT_FLOWS (" + fields + ") VALUES('АСОИ 32, 33','Примечание');");
    query.exec("INSERT INTO DRT_FLOWS (" + fields + ") VALUES('АСОИ 35, 34','Примечание');");

    query.exec("INSERT INTO DRT_FLOWS (" + fields + ") VALUES('ЭВМСиС 44, 45','Примечание');");
    query.exec("INSERT INTO DRT_FLOWS (" + fields + ") VALUES('ЭВМСиС 46, 47','Примечание');");
}

void DbService::createLinksTable() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_LINKS("
               "LNK_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "LNK_FLW_ID INTEGER NOT NULL, "
               "LNK_GRP_ID INTEGER NOT NULL, "
               "FOREIGN KEY(LNK_FLW_ID) REFERENCES DRT_FLOWS(FLW_ID), "
               "FOREIGN KEY(LNK_GRP_ID) REFERENCES DRT_GROUPS(GRP_ID));");

    QString fields("LNK_FLW_ID,LNK_GRP_ID");

    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(1,1);");
    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(1,2);");
    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(2,3);");
    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(2,4);");

    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(3,5);");
    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(3,6);");
    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(4,7);");
    query.exec("INSERT INTO DRT_LINKS (" + fields + ") VALUES(4,8);");
}

void DbService::createFlowsView() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE VIEW VIEW_FLOWS AS "
               "SELECT FLW.FLW_ID, FLW.FLW_NAME, GROUP_CONCAT(GRP.GRP_NAME, ', ') as FLW_GROUPS "
               "FROM DRT_FLOWS FLW, DRT_GROUPS GRP, DRT_LINKS LNK "
               "WHERE FLW.FLW_ID = LNK.LNK_FLW_ID "
               "AND LNK.LNK_GRP_ID = GRP.GRP_ID "
               "GROUP BY LNK.LNK_FLW_ID; ");
}

void DbService::createLoadCalculationView() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE VIEW VIEW_LOAD_CALCULATION AS "
               "SELECT LCL.LCL_ID AS LCLV_ID, printf('%s (%s)', DSC.DSC_NAME , VFLW.FLW_NAME) as LCLV_NAME "
               "FROM DRT_FLOWS FLW, DRT_LOAD_CALCULATION LCL, DRT_DISCIPLINES DSC, VIEW_FLOWS VFLW "
               "WHERE LCL.LCL_FLW_ID = VFLW.FLW_ID "
               "AND LCL.LCL_DSC_ID = DSC.DSC_ID "
               "GROUP BY LCL.LCL_ID");
}

void DbService::createLoadCalculation() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_LOAD_CALCULATION("
               "LCL_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "LCL_DSC_ID INTEGER NOT NULL, "
               "LCL_FLW_ID INTEGER NOT NULL, "
               "FOREIGN KEY(LCL_DSC_ID) REFERENCES DRT_DISCIPLINES(DSC_ID), "
               "FOREIGN KEY(LCL_FLW_ID) REFERENCES DRT_FLOWS(FLW_ID));");

    QString fields("LCL_DSC_ID,LCL_FLW_ID");

    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(1,1);");
    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(2,2);");
    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(2,3);");
    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(3,4);");
}

void DbService::createLoadDistribution() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_LOAD_DISTRIBUTION("
               "LDB_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "LDB_TCH_ID INTEGER NOT NULL, "
               "LDB_LCL_ID INTEGER NOT NULL, "
               "FOREIGN KEY(LDB_TCH_ID) REFERENCES DRT_TEACHERS(TCH_ID), "
               "FOREIGN KEY(LDB_LCL_ID) REFERENCES DRT_LOAD_CALCULATION(LCL_ID));");

    QString fields("LDB_TCH_ID,LDB_LCL_ID");

    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(1,1);");
    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(2,2);");
    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(3,3);");
    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(3,4);");
}
