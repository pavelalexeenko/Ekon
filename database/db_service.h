#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "objects/user.h"
#include "objects/teacher.h"
#include "objects/discipline.h"
#include "objects/group.h"
#include "objects/flow.h"
#include "objects/loadcalculation.h"
#include "objects/loaddistribution.h"
#include "objects/factors.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QDir>
#include <QSettings>

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
    Discipline getDisciplineById(const int& id);
    LoadCalculation getLoadCalculationById(const int& id);
    LoadCalculation getNotDistributedLoadById(const int& loadcalculationId);
    LoadDistribution getLoadDistributionById(const int& loadDistributionId);

    Factors getFactors() const;
    bool saveFactors(const Factors& factors);

    bool connectToAnotherDatabase(QString filename);
    bool loginAs(QString username, QString password);
    bool isLogged() const;
    bool testDatabaseConnection() const;

    bool addUser(const User& user);
    bool addTeacher(const Teacher& teacher);
    bool addDiscipline(const Discipline& discipline);
    bool addGroup(const Group& group);
    bool addFlow(const Flow& flow);
    bool updateFlow(const Flow& flow);
    bool addLoadCalculation(const int& disciplineId, const int& flowId);
    bool addLoadDistribution(const LoadDistribution& loadDistribution);
    bool updateLoadDistribution(const LoadDistribution& loadDistribution);

    bool deleteUser(const int& userId);
    bool deleteTeacher(const int& teacherId);
    bool deleteDiscipline(const int& disciplineId);
    bool deleteGroup(const int& groupId);
    bool deleteFlow(const int& flowId);
    bool deleteLoadCalculation(const int& lclId);
    bool deleteLoadDistribution(const int& ldId);

    QList<Group> getAllGroups() const;
    QList<Flow> getAllFlows() const;
    QList<Discipline> getAllDisciplines() const;
    QList<Teacher> getAllTeachers() const;
    QList<LoadCalculation> getAllLoadCalculation() const;

    QList<LoadDistribution> getLoadDistributionsByLoadCalculationId(const int loadCalculationId) const;

    QList<QPair<int, QString> > getLoadCalculationIdsAndNames() const;

    QList<int> getTeachersIdsForLoadCalculation(const int& lclId) const;

    int getStudentsNumberByFlowId(const int flowId) const;
    int getSubGroupsNumberByFlowId(const int flowId) const;

    QStringList exportLcl();
    QStringList exportLd();

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
    void createLoadCalculationTable() const;
    void createLoadDistributionTable() const;
    void createFlowsView() const;
    void createLoadCalculationView() const;
    void createLoadDistributionHelper() const;
    void createFactorsTable() const;

private:
    Factors toFactorsObject(const QSqlRecord& record) const;

    Group toGroupObject(const QSqlRecord& record) const;
    Flow toFlowObject(const QSqlRecord& record) const;
    Discipline toDisciplineObject(const QSqlRecord& record) const;
    Teacher toTeacherObject(const QSqlRecord& record) const;
    LoadCalculation toLoadCalculationObject(const QSqlRecord& record) const;
    LoadDistribution toLoadDistributionObject(const QSqlRecord& record) const;

    QString toExportLclString(const QSqlRecord& record) const;
    QString toExportLdString(const QSqlRecord& record) const;

    QSet<int> getGroupsIdsByFlowId(const int& flowId) const;

private:
    const QString _defaultDatabaseFilename;
    QSharedPointer<User> _currentUser;
    QSharedPointer<QSqlDatabase> _db;

};

#endif // DBSERVICE_H


