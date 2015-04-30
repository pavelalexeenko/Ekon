#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "objects/user.h"
#include "objects/teacher.h"
#include "objects/discipline.h"
#include "objects/group.h"
#include "objects/flow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QDir>

#include <QStringList>
#include <QSharedPointer>

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
    QStringList getAllUserroles() const;
    QSharedPointer<User> getCurrentUser() const;
    QString getCurrentDataBasePath() const;
    QString getLastError() const;

    QString getGroupNameById(const int& id);
    Flow getFlowById(const int& id);

    bool connectToAnotherDatabase(QString filename);
    bool loginAs(QString username, QString password);
    bool testDatabaseConnection() const;

    bool addUser(const User& user);
    bool addTeacher(const Teacher& teacher);
    bool addDiscipline(const Discipline& discipline);
    bool addGroup(const Group& group);
    bool addFlow(const Flow& flow);
    bool updateFlow(const Flow& flow);

    QList<Group> getAllGroups() const;
    QList<Flow> getAllFlows() const;

private:
    bool isCorrectVersion() const;

    void createDatabase() const;
    void removeCurrentFile() const;

    void createUsersTypesTable() const;
    void createUsersTable() const;
    void createDisciplinesTable() const;
    void createTeachersTable() const;
    void createGroupsTable() const;
    void createFlowsTable() const;
    void createLinksTable() const;
    void createLoadCalculation() const;
    void createLoadDistribution() const;

    void createFlowsView() const;
    void createLoadCalculationView() const;

private:
    Group toGroupObject(const QSqlRecord& record) const;
    Flow toFlowObject(const QSqlRecord& record) const;

    QSet<int> getGroupsIdsByFlowId(const int& flowId) const;

private:
    const QString _defaultDatabaseFilename;
    QSharedPointer<User> _currentUser;
    QSharedPointer<QSqlDatabase> _db;

};

#endif // DBSERVICE_H


