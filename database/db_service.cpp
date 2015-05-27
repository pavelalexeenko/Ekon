#include "db_service.h"

DbService* DbService::_instance = 0;

DbService::DbService() :
    _defaultDatabaseFilename("db.sqlite"),
    _currentUser(new User())
{
    qDebug() << __FUNCTION__;

    _db.reset(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")));
    _db->setDatabaseName(_defaultDatabaseFilename);

    if (QFile::exists(_defaultDatabaseFilename))
    {
        qDebug() << "File already exists";
        if (_db->open())
            if (!isCorrectVersion())
            {
                qDebug() << "Creating database";
                createDatabase();
            }
            else
            {
                qDebug() << "Version is correct";
            }
    }
    else
    {
        qDebug() << "There is no database file. Creating database";
        createDatabase();
    }
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

    _db->transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) "
                  "VALUES (:username, :password, :type)");
    query.bindValue(":username", user.getUsername());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":type", user.getUserrole());

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::addTeacher(const Teacher &teacher)
{
    qDebug() << __FUNCTION__;

    _db->transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO DRT_TEACHERS (TCH_NAME, TCH_RATE, TCH_INFO) "
                  "VALUES (:name, :rate, :info)");
    query.bindValue(":name", teacher.getName());
    query.bindValue(":rate", teacher.getRate());
    query.bindValue(":info", teacher.getInfo());

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::addDiscipline(const Discipline &discipline)
{
    qDebug() << __FUNCTION__;

    QString fields("DSC_NAME,DSC_LECTURES,DSC_LABORATORY,DSC_PRACTICAL,DSC_CONSULTATION,DSC_EXAMINATIONS,DSC_TESTS,DSC_CURRENT_CONSULTATION, "
                   "DSC_INTRODUCTORY_PRACTICE,DSC_PRE_DIPLOMA_PRACTICE,DSC_COURSEWORK,DSC_GUIDED_INDEPENDENT_WORK,DSC_CONTROL_WORK, "
                   "DSC_GRADUATION_DESIGN,DSC_GUIDE_GRADUATE,DSC_STATE_EXAM,DSC_HES,DSC_GUIDE_CHAIR,DSC_UIRS");

    _db->transaction();
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
    query.bindValue(":guIndWork", discipline.hasGuidedIndependentWork());
    query.bindValue(":contrl", discipline.hasControlWork());
    query.bindValue(":gradDesign", discipline.hasGraduationDesign());
    query.bindValue(":guGrad", discipline.hasGuideGraduate());
    query.bindValue(":stateExam", discipline.hasStateExam());
    query.bindValue(":hes", discipline.hasHes());
    query.bindValue(":guideChair", discipline.hasGuideChair());
    query.bindValue(":uirs", discipline.hasUirs());

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::addGroup(const Group& group)
{
    qDebug() << __FUNCTION__;

    QString fields("GRP_NAME,GRP_NUMBER_OF_STUDENTS,GRP_COURSE,GRP_NUMBER_OF_SUBGROUPS,GRP_SEMESTR,GRP_FACULTET,GRP_SPECIALITY,GRP_NOTE");
    _db->transaction();
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
        return !_db->rollback();

    return _db->commit();
}

bool DbService::addFlow(const Flow &flow)
{
    qDebug() << __FUNCTION__;

    _db->transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO DRT_FLOWS (FLW_NAME,FLW_NOTE) VALUES(:name, :note);");

    query.bindValue(":name", flow.getName());
    query.bindValue(":note", flow.getNote());

    if (!query.exec())
        return !_db->rollback();;

    int id = query.lastInsertId().toInt();

    for (auto groupId : flow.getGroupIds())
    {
        query.prepare("INSERT INTO DRT_LINKS (LNK_FLW_ID,LNK_GRP_ID) VALUES(:flowId, :groupId);");
        query.bindValue(":flowId", id);
        query.bindValue(":groupId", groupId);

        if (!query.exec())
            return !_db->rollback();
    }

    return _db->commit();;
}

bool DbService::updateFlow(const Flow &flow)
{
    qDebug() << __FUNCTION__;

    _db->transaction();
    QSqlQuery query;
    query.prepare("UPDATE DRT_FLOWS SET FLW_NAME = :name, FLW_NOTE = :note WHERE FLW_ID = :flowId");

    query.bindValue(":name", flow.getName());
    query.bindValue(":note", flow.getNote());
    query.bindValue(":flowId", flow.getId());

    if (!query.exec())
        return !_db->rollback();

    query.prepare("DELETE FROM DRT_LINKS WHERE LNK_FLW_ID = :flowId;");
    query.bindValue(":flowId", flow.getId());
    if (!query.exec())
        return !_db->rollback();

    for (auto groupId : flow.getGroupIds())
    {
        query.prepare("INSERT INTO DRT_LINKS (LNK_FLW_ID,LNK_GRP_ID) VALUES(:flowId, :groupId);");
        query.bindValue(":flowId", flow.getId());
        query.bindValue(":groupId", groupId);

        if (!query.exec())
            return !_db->rollback();
    }

    return _db->commit();
}

bool DbService::addLoadCalculation(const int &disciplineId, const int &flowId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO DRT_LOAD_CALCULATION (LCL_DSC_ID,LCL_FLW_ID) VALUES(:disciplineId, :flowId);");
    query.bindValue(":disciplineId", disciplineId);
    query.bindValue(":flowId", flowId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::addLoadDistribution(const LoadDistribution &loadDistribution)
{
    qDebug() << __FUNCTION__;

    QString fields("LDB_TCH_ID, LDB_LCL_ID, LDB_LECTURES, LDB_LABORATORY, LDB_PRACTICAL ,LDB_CONSULTATION ,LDB_EXAMINATIONS, "
                   "LDB_TESTS ,LDB_CURRENT_CONSULTATION ,LDB_INTRODUCTORY_PRACTICE ,LDB_PRE_DIPLOMA_PRACTICE ,LDB_COURSEWORK, "
                   "LDB_GUIDED_INDEPENDENT_WORK ,LDB_CONTROL_WORK ,LDB_GRADUATION_DESIGN,LDB_GUIDE_GRADUATE ,LDB_STATE_EXAM, "
                   "LDB_HES,LDB_GUIDE_CHAIR,LDB_UIRS");

    _db->transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") "
                                                                   "VALUES (:teacherId, :lclId, :lec, :lab, :prac, :consult, :exam, :tests, :curCons, :intrPrac, :preDiplPrac, :course, :guIndWork, :contrl, "
                                                                   " :gradDesign, :guGrad, :stateExam, :hes, :guideChair, :uirs)");

    query.bindValue(":teacherId", loadDistribution.getTeacherId());
    query.bindValue(":lclId", loadDistribution.getLoadCalculaionId());
    query.bindValue(":lec", loadDistribution.getLectures());
    query.bindValue(":lab", loadDistribution.getLaboratory());
    query.bindValue(":prac", loadDistribution.getPractical());
    query.bindValue(":consult", loadDistribution.getConsultation());
    query.bindValue(":exam", loadDistribution.getExamination());
    query.bindValue(":tests", loadDistribution.getTests());
    query.bindValue(":curCons", loadDistribution.getCurrentConsultation());
    query.bindValue(":intrPrac", loadDistribution.getIntroductoryPractice());
    query.bindValue(":preDiplPrac", loadDistribution.getPreDiplomaPractice());
    query.bindValue(":course", loadDistribution.getCourseWork());
    query.bindValue(":guIndWork", loadDistribution.getGuideIndependentWork());
    query.bindValue(":contrl", loadDistribution.getControlWork());
    query.bindValue(":gradDesign", loadDistribution.getGraduationDesign());
    query.bindValue(":guGrad", loadDistribution.getGuideGraduate());
    query.bindValue(":stateExam", loadDistribution.getStateExam());
    query.bindValue(":hes", loadDistribution.getHes());
    query.bindValue(":guideChair", loadDistribution.getGuideChair());
    query.bindValue(":uirs", loadDistribution.getUirs());

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::updateLoadDistribution(const LoadDistribution &loadDistribution)
{
    qDebug() << __FUNCTION__;

    _db->transaction();
    QSqlQuery query;
    query.prepare("UPDATE DRT_LOAD_DISTRIBUTION SET "
                  "LDB_TCH_ID = :teacherId, LDB_LCL_ID = :lclId, LDB_LECTURES = :lec, LDB_LABORATORY = :lab, LDB_PRACTICAL = :prac, "
                  "LDB_CONSULTATION = :consult, LDB_EXAMINATIONS = :exam, LDB_TESTS = :tests, LDB_CURRENT_CONSULTATION = :curCons, "
                  "LDB_INTRODUCTORY_PRACTICE = :intrPrac, LDB_PRE_DIPLOMA_PRACTICE = :preDiplPrac, LDB_COURSEWORK = :course, "
                  "LDB_GUIDED_INDEPENDENT_WORK = :guIndWork, LDB_CONTROL_WORK = :contrl, LDB_GRADUATION_DESIGN = :gradDesign, "
                  "LDB_GUIDE_GRADUATE = :guGrad, LDB_STATE_EXAM = :stateExam, LDB_HES = :hes, LDB_GUIDE_CHAIR = :guideChair, LDB_UIRS = :uirs "
                  "WHERE LDB_ID = :id");

    query.bindValue(":id", loadDistribution.getId());
    query.bindValue(":teacherId", loadDistribution.getTeacherId());
    query.bindValue(":lclId", loadDistribution.getLoadCalculaionId());
    query.bindValue(":lec", loadDistribution.getLectures());
    query.bindValue(":lab", loadDistribution.getLaboratory());
    query.bindValue(":prac", loadDistribution.getPractical());
    query.bindValue(":consult", loadDistribution.getConsultation());
    query.bindValue(":exam", loadDistribution.getExamination());
    query.bindValue(":tests", loadDistribution.getTests());
    query.bindValue(":curCons", loadDistribution.getCurrentConsultation());
    query.bindValue(":intrPrac", loadDistribution.getIntroductoryPractice());
    query.bindValue(":preDiplPrac", loadDistribution.getPreDiplomaPractice());
    query.bindValue(":course", loadDistribution.getCourseWork());
    query.bindValue(":guIndWork", loadDistribution.getGuideIndependentWork());
    query.bindValue(":contrl", loadDistribution.getControlWork());
    query.bindValue(":gradDesign", loadDistribution.getGraduationDesign());
    query.bindValue(":guGrad", loadDistribution.getGuideGraduate());
    query.bindValue(":stateExam", loadDistribution.getStateExam());
    query.bindValue(":hes", loadDistribution.getHes());
    query.bindValue(":guideChair", loadDistribution.getGuideChair());
    query.bindValue(":uirs", loadDistribution.getUirs());

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::deleteUser(const int &userId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM DRT_USERS WHERE USER_ID = :id;");
    query.bindValue(":id", userId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::deleteTeacher(const int &teacherId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM DRT_TEACHERS WHERE TCH_ID = :id;");
    query.bindValue(":id", teacherId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::deleteDiscipline(const int &disciplineId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM DRT_DISCIPLINES WHERE DSC_ID = :id;");
    query.bindValue(":id", disciplineId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::deleteGroup(const int &groupId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM DRT_GROUPS WHERE GRP_ID = :id;");
    query.bindValue(":id", groupId);

    if (!query.exec())
        return !_db->rollback();

    query.prepare("DELETE FROM DRT_LINKS WHERE LNK_GRP_ID = :id;");
    query.bindValue(":id", groupId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::deleteFlow(const int &flowId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM DRT_FLOWS WHERE FLW_ID = :id;");
    query.bindValue(":id", flowId);

    if (!query.exec())
        return !_db->rollback();

    query.prepare("DELETE FROM DRT_LINKS WHERE LNK_FLW_ID = :id;");
    query.bindValue(":id", flowId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::deleteLoadCalculation(const int &lclId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM DRT_LOAD_CALCULATION WHERE LCL_ID = :id;");
    query.bindValue(":id", lclId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

bool DbService::deleteLoadDistribution(const int &ldId)
{
    qDebug() << __FUNCTION__;
    _db->transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM DRT_LOAD_DISTRIBUTION WHERE LDB_ID = :id;");
    query.bindValue(":id", ldId);

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
}

QString DbService::getGroupNameById(const int &id)
{
    QSqlQuery query;
    query.prepare("SELECT GRP_NAME FROM DRT_GROUPS WHERE GRP_ID = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return query.record().value("GRP_NAME").toString();
}

Flow DbService::getFlowById(const int &id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_FLOWS WHERE FLW_ID = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return toFlowObject(query.record());
}

Discipline DbService::getDisciplineById(const int &id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_DISCIPLINES WHERE DSC_ID = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return toDisciplineObject(query.record());
}

LoadCalculation DbService::getLoadCalculationById(const int &id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM VIEW_LOAD_CALCULATION WHERE LCLV_ID = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return toLoadCalculationObject(query.record());
}

LoadCalculation DbService::getNotDistributedLoadById(const int &loadcalculationId)
{
    LoadCalculation lcl = getLoadCalculationById(loadcalculationId);
    QList<LoadDistribution> lds = getLoadDistributionsByLoadCalculationId(loadcalculationId);

    for (LoadDistribution ld : lds)
    {
        if (ld.getLoadCalculaionId() != lcl.getId())
            throw QString("Function take wrong loaddistribution list from database");

        lcl.setLectures(lcl.getLectures() - ld.getLectures());
        lcl.setLaboratory(lcl.getLaboratory() - ld.getLaboratory());
        lcl.setPractical(lcl.getPractical() - ld.getPractical());
        lcl.setConsultation(lcl.getConsultation() - ld.getConsultation());
        lcl.setExaminations(lcl.getExamination() - ld.getExamination());
        lcl.setTests(lcl.getTests() - ld.getTests());
        lcl.setCurrentConsultation(lcl.getCurrentConsultation() - ld.getCurrentConsultation());
        lcl.setIntroductoryPractice(lcl.getIntroductoryPractice() - ld.getIntroductoryPractice());
        lcl.setPreDiplomaPractice(lcl.getPreDiplomaPractice() - ld.getPreDiplomaPractice());
        lcl.setCourseWork(lcl.getCourseWork() - ld.getCourseWork());
        lcl.setGuideIndependentWork(lcl.getGuideIndependentWork() - ld.getGuideIndependentWork());
        lcl.setControlWork(lcl.getControlWork() - ld.getControlWork());
        lcl.setGraduationDesign(lcl.getGraduationDesign() - ld.getGraduationDesign());
        lcl.setGuideGraduate(lcl.getGuideGraduate() - ld.getGuideGraduate());
        lcl.setStateExam(lcl.getStateExam() - ld.getStateExam());
        lcl.setHes(lcl.getHes() - ld.getHes());
        lcl.setGuideChair(lcl.getGuideChair() - ld.getGuideChair());
        lcl.setUirs(lcl.getUirs() - ld.getUirs());
    }

    return lcl;
}

LoadDistribution DbService::getLoadDistributionById(const int &loadDistributionId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_LOAD_DISTRIBUTION WHERE LDB_ID = :id");
    query.bindValue(":id", loadDistributionId);

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return toLoadDistributionObject(query.record());
}

Factors DbService::getFactors() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_FACTORS WHERE FCT_ID = 1");

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return toFactorsObject(query.record());
}

bool DbService::saveFactors(const Factors &factors)
{
    qDebug() << __FUNCTION__;

    _db->transaction();
    QSqlQuery query;
    query.prepare("UPDATE DRT_FACTORS SET "
                  "FCT_CONSULTATION = :consult, FCT_EXAMINATIONS = :exam, FCT_TESTS = :tests, FCT_CURRENT_CONSULTATION = :curCons, "
                  "FCT_INTRODUCTORY_PRACTICE = :intrPrac, FCT_PRE_DIPLOMA_PRACTICE = :preDiplPrac, FCT_COURSEWORK = :course, "
                  "FCT_GUIDED_INDEPENDENT_WORK = :guIndWork, FCT_CONTROL_WORK = :contrl, FCT_GRADUATION_DESIGN = :gradDesign, "
                  "FCT_GUIDE_GRADUATE = :guGrad, FCT_STATE_EXAM = :stateExam, FCT_HES = :hes, FCT_GUIDE_CHAIR = :guideChair, FCT_UIRS = :uirs "
                  "WHERE FCT_ID = 1");

    query.bindValue(":consult", factors.getConsultationFactor());
    query.bindValue(":exam", factors.getExaminationFactor());
    query.bindValue(":tests", factors.getTestsFactor());
    query.bindValue(":curCons", factors.getCurrentConsultationFactor());
    query.bindValue(":intrPrac", factors.getIntroductoryPracticeFactor());
    query.bindValue(":preDiplPrac", factors.getPreDiplomaPracticeFactor());
    query.bindValue(":course", factors.getCourseWorkFactor());
    query.bindValue(":guIndWork", factors.getGuidedIndependentWorkFactor());
    query.bindValue(":contrl", factors.getControlWorkFactor());
    query.bindValue(":gradDesign", factors.getGraduationDesignFactor());
    query.bindValue(":guGrad", factors.getGuideGraduateFactor());
    query.bindValue(":stateExam", factors.getStateExamFactor());
    query.bindValue(":hes", factors.getHesFactor());
    query.bindValue(":guideChair", factors.getGuideChairFactor());
    query.bindValue(":uirs", factors.getUirsFactor());

    if (!query.exec())
        return !_db->rollback();

    return _db->commit();
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

    QList<Flow> flows;

    while(query.next())
        flows.append(toFlowObject(query.record()));

    return flows;
}

QList<Discipline> DbService::getAllDisciplines() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_DISCIPLINES ORDER BY DSC_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    QList<Discipline> disciplines;

    while(query.next())
        disciplines.append(toDisciplineObject(query.record()));

    return disciplines;
}

QList<Teacher> DbService::getAllTeachers() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_TEACHERS ORDER BY TCH_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    QList<Teacher> teachers;

    while(query.next())
        teachers.append(toTeacherObject(query.record()));

    return teachers;
}

QList<LoadCalculation> DbService::getAllLoadCalculation() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM VIEW_LOAD_CALCULATION ORDER BY LVLV_DSC_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    QList<LoadCalculation> lcls;

    while(query.next())
        lcls.append(toLoadCalculationObject(query.record()));

    return lcls;
}

QList<LoadDistribution> DbService::getLoadDistributionsByLoadCalculationId(const int loadCalculationId) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DRT_LOAD_DISTRIBUTION WHERE LDB_LCL_ID = :lclId");
    query.bindValue(":lclId", loadCalculationId);

    if (!query.exec())
        throw QString(query.lastError().text());

    QList<LoadDistribution> lds;

    while(query.next())
        lds.append(toLoadDistributionObject(query.record()));

    return lds;
}

QList<QPair<int, QString> > DbService::getLoadCalculationIdsAndNames() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM VIEW_LOAD_DISTRIBUTION_HELPER ORDER BY LDH_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    QList<QPair<int, QString> > result;

    while(query.next())
    {
        int id = query.record().value("LDH_ID").toInt();
        QString name = query.record().value("LDH_NAME").toString();
        result.append(qMakePair(id, name));
    }

    return result;
}

QList<int> DbService::getTeachersIdsForLoadCalculation(const int &lclId) const
{
    QSqlQuery query;
    query.prepare("SELECT LDB_TCH_ID FROM DRT_LOAD_DISTRIBUTION WHERE LDB_LCL_ID = :lclId");
    query.bindValue(":lclId", lclId);

    if (!query.exec())
        throw QString(query.lastError().text());

    QList<int> ids;

    while(query.next())
        ids.append(query.record().value("LDB_TCH_ID").toInt());

    return ids;
}

int DbService::getStudentsNumberByFlowId(const int flowId) const
{
    QSqlQuery query;
    query.prepare("SELECT LNK.LNK_FLW_ID as FLW_ID, TOTAL(GRP.GRP_NUMBER_OF_STUDENTS) as STUDENTS_NUMBER "
                  "FROM DRT_GROUPS GRP, DRT_LINKS LNK "
                  "WHERE GRP.GRP_ID = LNK.LNK_GRP_ID AND LNK.LNK_FLW_ID = :flowId ");
    query.bindValue(":flowId", flowId);

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return query.record().value("STUDENTS_NUMBER").toInt();
}

int DbService::getSubGroupsNumberByFlowId(const int flowId) const
{
    QSqlQuery query;
    query.prepare("SELECT LNK.LNK_FLW_ID as FLW_ID, TOTAL(GRP.GRP_NUMBER_OF_SUBGROUPS) as SUBGROUPS_NUMBER "
                  "FROM DRT_GROUPS GRP, DRT_LINKS LNK "
                  "WHERE GRP.GRP_ID = LNK.LNK_GRP_ID AND LNK.LNK_FLW_ID = :flowId ");
    query.bindValue(":flowId", flowId);

    if (!query.exec())
        throw QString(query.lastError().text());

    if (!query.first())
        throw QString(query.lastError().text());

    return query.record().value("SUBGROUPS_NUMBER").toInt();
}

Factors DbService::toFactorsObject(const QSqlRecord &record) const
{
    Factors factors;
    factors.setId(record.value("FCT_ID").toInt());
    factors.setConsultationFactor(record.value("FCT_CONSULTATION").toDouble());
    factors.setExaminationsFactor(record.value("FCT_EXAMINATIONS").toDouble());
    factors.setTestsFactor(record.value("FCT_TESTS").toDouble());
    factors.setCurrentConsultationFactor(record.value("FCT_CURRENT_CONSULTATION").toDouble());
    factors.setIntroductoryPracticeFactor(record.value("FCT_INTRODUCTORY_PRACTICE").toDouble());
    factors.setPreDiplomaPracticeFactor(record.value("FCT_PRE_DIPLOMA_PRACTICE").toDouble());
    factors.setCourseWorkFactor(record.value("FCT_COURSEWORK").toDouble());
    factors.setGuidedIndependentWorkFactor(record.value("FCT_ID").toDouble());
    factors.setControlWorkFactor(record.value("FCT_CONTROL_WORK").toDouble());
    factors.setGraduationDesignFactor(record.value("FCT_GRADUATION_DESIGN").toDouble());
    factors.setGuideGraduateFactor(record.value("FCT_GUIDE_GRADUATE").toDouble());
    factors.setStateExamFactor(record.value("FCT_STATE_EXAM").toDouble());
    factors.setHesFactor(record.value("FCT_HES").toDouble());
    factors.setGuideChairFactor(record.value("FCT_GUIDE_CHAIR").toDouble());
    factors.setUirsFactor(record.value("FCT_UIRS").toDouble());

    return factors;
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

Discipline DbService::toDisciplineObject(const QSqlRecord &record) const
{
    Discipline discipline;
    discipline.setId(record.value("DSC_ID").toInt());
    discipline.setName(record.value("DSC_NAME").toString());
    discipline.setLectures(record.value("DSC_LECTURES").toDouble());
    discipline.setLaboratory(record.value("DSC_LABORATORY").toDouble());
    discipline.setPractical(record.value("DSC_PRACTICAL").toDouble());
    discipline.setConsultation(record.value("DSC_CONSULTATION").toBool());
    discipline.setExaminations(record.value("DSC_EXAMINATIONS").toBool());
    discipline.setTests(record.value("DSC_TESTS").toBool());
    discipline.setCurrentConsultation(record.value("DSC_CURRENT_CONSULTATION").toBool());
    discipline.setIntroductoryPractice(record.value("DSC_INTRODUCTORY_PRACTICE").toBool());
    discipline.setPreDiplomaPractice(record.value("DSC_PRE_DIPLOMA_PRACTICE").toBool());
    discipline.setCourseWork(record.value("DSC_COURSEWORK").toBool());
    discipline.setGuidedIndependentWork(record.value("DSC_GUIDED_INDEPENDENT_WORK").toBool());
    discipline.setControlWork(record.value("DSC_CONTROL_WORK").toBool());
    discipline.setGraduationDesign(record.value("DSC_GRADUATION_DESIGN").toBool());
    discipline.setGuideGraduate(record.value("DSC_GUIDE_GRADUATE").toBool());
    discipline.setStateExam(record.value("DSC_STATE_EXAM").toBool());
    discipline.setHes(record.value("DSC_HES").toBool());
    discipline.setGuideChair(record.value("DSC_GUIDE_CHAIR").toBool());
    discipline.setUirs(record.value("DSC_UIRS").toBool());

    return discipline;
}

Teacher DbService::toTeacherObject(const QSqlRecord &record) const
{
    Teacher teacher;
    teacher.setId(record.value("TCH_ID").toInt());
    teacher.setName(record.value("TCH_NAME").toString());
    teacher.setRate(record.value("TCH_RATE").toDouble());
    teacher.setInfo(record.value("TCH_INFO").toString());

    return teacher;
}

LoadCalculation DbService::toLoadCalculationObject(const QSqlRecord &record) const
{
    LoadCalculation lcl;
    lcl.setId(record.value("LCLV_ID").toInt());
    lcl.setFlowId(record.value("LCLV_FLW_ID").toInt());
    lcl.setDisciplineId(record.value("LVLV_DSC_ID").toInt());
    lcl.setLectures(record.value("LCLV_LECTURES").toDouble());
    lcl.setLaboratory(record.value("LCLV_LABORATORY").toDouble());
    lcl.setPractical(record.value("LCLV_PRACTICAL").toDouble());
    lcl.setConsultation(record.value("LCLV_CONSULTATION").toDouble());
    lcl.setExaminations(record.value("LCLV_EXAMINATIONS").toDouble());
    lcl.setTests(record.value("LCLV_TESTS").toDouble());
    lcl.setCurrentConsultation(record.value("LCLV_CURRENT_CONSULTATION").toDouble());
    lcl.setIntroductoryPractice(record.value("LCLV_INTRODUCTORY_PRACTICE").toDouble());
    lcl.setPreDiplomaPractice(record.value("LCLV_PRE_DIPLOMA_PRACTICE").toDouble());
    lcl.setCourseWork(record.value("LCLV_COURSEWORK").toDouble());
    lcl.setGuideIndependentWork(record.value("LCLV_GUIDED_INDEPENDENT_WORK").toDouble());
    lcl.setControlWork(record.value("LCLV_CONTROL_WORK").toDouble());
    lcl.setGraduationDesign(record.value("LCLV_GRADUATION_DESIGN").toDouble());
    lcl.setGuideGraduate(record.value("LCLV_GUIDE_GRADUATE").toDouble());
    lcl.setStateExam(record.value("LCLV_STATE_EXAM").toDouble());
    lcl.setHes(record.value("LCLV_HES").toDouble());
    lcl.setGuideChair(record.value("LCLV_GUIDE_CHAIR").toDouble());
    lcl.setUirs(record.value("LCLV_UIRS").toDouble());

    return lcl;
}

LoadDistribution DbService::toLoadDistributionObject(const QSqlRecord &record) const
{
    LoadDistribution ld;
    ld.setId(record.value("LDB_ID").toInt());
    ld.setTeacherId(record.value("LDB_TCH_ID").toInt());
    ld.setLoadCalculaionId(record.value("LDB_LCL_ID").toInt());
    ld.setLectures(record.value("LDB_LECTURES").toDouble());
    ld.setLaboratory(record.value("LDB_LABORATORY").toDouble());
    ld.setPractical(record.value("LDB_PRACTICAL").toDouble());
    ld.setConsultation(record.value("LDB_CONSULTATION").toDouble());
    ld.setExaminations(record.value("LDB_EXAMINATIONS").toDouble());
    ld.setTests(record.value("LDB_TESTS").toDouble());
    ld.setCurrentConsultation(record.value("LDB_CURRENT_CONSULTATION").toDouble());
    ld.setIntroductoryPractice(record.value("LDB_INTRODUCTORY_PRACTICE").toDouble());
    ld.setPreDiplomaPractice(record.value("LDB_PRE_DIPLOMA_PRACTICE").toDouble());
    ld.setCourseWork(record.value("LDB_COURSEWORK").toDouble());
    ld.setGuideIndependentWork(record.value("LDB_GUIDED_INDEPENDENT_WORK").toDouble());
    ld.setControlWork(record.value("LDB_CONTROL_WORK").toDouble());
    ld.setGraduationDesign(record.value("LDB_GRADUATION_DESIGN").toDouble());
    ld.setGuideGraduate(record.value("LDB_GUIDE_GRADUATE").toDouble());
    ld.setStateExam(record.value("LDB_STATE_EXAM").toDouble());
    ld.setHes(record.value("LDB_HES").toDouble());
    ld.setGuideChair(record.value("LDB_GUIDE_CHAIR").toDouble());
    ld.setUirs(record.value("LDB_UIRS").toDouble());

    return ld;
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
        throw QString("Can't open database: %1").arg(_db->lastError().text());
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
    tablesList.append(QString("DRT_FACTORS"));

    tablesList.append(QString("VIEW_FLOWS"));
    tablesList.append(QString("VIEW_LOAD_CALCULATION"));

    tablesList.append(QString("VIEW_LOAD_DISTRIBUTION_HELPER"));

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

bool DbService::isLogged() const
{
    return _currentUser.data()->getUserrole() != User::USER_ROLE_UNDEFINED;
}

void DbService::createDatabase() const
{
    qDebug() << __FUNCTION__;

    removeCurrentFile();

    QSqlDatabase::database().transaction();
    createUsersTypesTable();
    createUsersTable();
    createFactorsTable();
    createDisciplinesTable();
    createTeachersTable();
    createGroupsTable();
    createFlowsTable();
    createLinksTable();
    createFlowsView();
    createLoadCalculationTable();
    createLoadDistributionTable();
    createLoadCalculationView();
    createLoadDistributionHelper();
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

void DbService::createFactorsTable() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_FACTORS("
               "FCT_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "FCT_CONSULTATION REAL NOT NULL DEFAULT 0, "
               "FCT_EXAMINATIONS REAL NOT NULL DEFAULT 0, "
               "FCT_TESTS REAL NOT NULL DEFAULT 0, "
               "FCT_CURRENT_CONSULTATION REAL NOT NULL DEFAULT 0, "
               "FCT_INTRODUCTORY_PRACTICE REAL NOT NULL DEFAULT 0, "
               "FCT_PRE_DIPLOMA_PRACTICE REAL NOT NULL DEFAULT 0, "
               "FCT_COURSEWORK REAL NOT NULL DEFAULT 0, "
               "FCT_GUIDED_INDEPENDENT_WORK REAL NOT NULL DEFAULT 0, "
               "FCT_CONTROL_WORK REAL NOT NULL DEFAULT 0, "
               "FCT_GRADUATION_DESIGN REAL NOT NULL DEFAULT 0, "
               "FCT_GUIDE_GRADUATE REAL NOT NULL DEFAULT 0, "
               "FCT_STATE_EXAM REAL NOT NULL DEFAULT 0, "
               "FCT_HES REAL NOT NULL DEFAULT 0, "
               "FCT_GUIDE_CHAIR REAL NOT NULL DEFAULT 0, "
               "FCT_UIRS REAL NOT NULL DEFAULT 0 "
               ");");

    QString fields("FCT_CONSULTATION,FCT_EXAMINATIONS,FCT_TESTS,FCT_CURRENT_CONSULTATION,FCT_INTRODUCTORY_PRACTICE,"
                   "FCT_PRE_DIPLOMA_PRACTICE,FCT_COURSEWORK,FCT_GUIDED_INDEPENDENT_WORK,FCT_CONTROL_WORK,"
                   "FCT_GRADUATION_DESIGN,FCT_GUIDE_GRADUATE,FCT_STATE_EXAM,FCT_HES,FCT_GUIDE_CHAIR,FCT_UIRS");

    query.exec("INSERT INTO DRT_FACTORS (" + fields + ") VALUES (1,2,3,4,5,6,7,8,9,1.0,1.1,1.2,1.3,1.4,1.5);");
}

void DbService::createUsersTypesTable() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_USER_TYPES("
               "UST_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "UST_NAME VARCHAR(50) NOT NULL UNIQUE);");
    query.exec("INSERT INTO DRT_USER_TYPES (UST_ID, UST_NAME) VALUES (0, 'Администратор');");
    query.exec("INSERT INTO DRT_USER_TYPES (UST_ID, UST_NAME) VALUES (1, 'Заведующий кафедрой');");
    query.exec("INSERT INTO DRT_USER_TYPES (UST_ID, UST_NAME) VALUES (2, 'Секретарь кафедры');");
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
    query.exec("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) VALUES('Администратор', '123', 0);");
    query.exec("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) VALUES('Заведующий кафедрой', '123', 1);");
    query.exec("INSERT INTO DRT_USERS (USER_USERNAME, USER_PASSWORD, USER_TYPE_ID) VALUES('Секретарь кафедры', '123', 2);");
}

void DbService::createDisciplinesTable() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_DISCIPLINES("
               "DSC_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "DSC_NAME VARCHAR(100) NOT NULL UNIQUE, "
               "DSC_LECTURES REAL NOT NULL DEFAULT 0, "
               "DSC_LABORATORY REAL NOT NULL DEFAULT 0, "
               "DSC_PRACTICAL REAL NOT NULL DEFAULT 0, "
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

    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-32', 19, 5, 1, 9,'ЭИС','АСОИ','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-33', 20, 5, 2, 9,'ЭИС','АСОИ','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-34', 25, 4, 3, 7,'ЭИС','АСОИ','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('АС-35', 22, 4, 4, 7,'ЭИС','АСОИ','Примечание');");

    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-44', 15, 5, 5, 9,'ЭИС','ЭВМСиС','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-45', 16, 5, 6, 9,'ЭИС','ЭВМСиС','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-46', 22, 4, 7, 7,'ЭИС','ЭВМСиС','Примечание');");
    query.exec("INSERT INTO DRT_GROUPS (" + fields + ") VALUES('Э-47', 25, 4, 8, 7,'ЭИС','ЭВМСиС','Примечание');");
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
               "SELECT "
               "FLW.FLW_ID, "
               "FLW.FLW_NAME, "
               "GROUP_CONCAT(GRP.GRP_NAME, ', ') as FLW_GROUPS, FLW.FLW_NOTE "
               "FROM DRT_FLOWS FLW, DRT_GROUPS GRP, DRT_LINKS LNK "
               "WHERE FLW.FLW_ID = LNK.LNK_FLW_ID "
               "AND LNK.LNK_GRP_ID = GRP.GRP_ID "
               "GROUP BY LNK.LNK_FLW_ID; ");
}

void DbService::createLoadCalculationTable() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_LOAD_CALCULATION("
               "LCL_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "LCL_DSC_ID INTEGER NOT NULL, "
               "LCL_FLW_ID INTEGER NOT NULL, "
               "FOREIGN KEY(LCL_DSC_ID) REFERENCES DRT_DISCIPLINES(DSC_ID) ON DELETE CASCADE ON UPDATE CASCADE, "
               "FOREIGN KEY(LCL_FLW_ID) REFERENCES DRT_FLOWS(FLW_ID) ON DELETE CASCADE ON UPDATE CASCADE);");

    QString fields("LCL_DSC_ID,LCL_FLW_ID");

    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(1,1);");
    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(2,2);");
    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(2,3);");
    query.exec("INSERT INTO DRT_LOAD_CALCULATION (" + fields + ") VALUES(3,4);");
}

void DbService::createLoadDistributionTable() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE TABLE DRT_LOAD_DISTRIBUTION("
               "LDB_ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
               "LDB_TCH_ID INTEGER NOT NULL, "
               "LDB_LCL_ID INTEGER NOT NULL, "
               "LDB_LECTURES REAL, "
               "LDB_LABORATORY REAL, "
               "LDB_PRACTICAL REAL, "
               "LDB_CONSULTATION REAL, "
               "LDB_EXAMINATIONS REAL, "
               "LDB_TESTS REAL, "
               "LDB_CURRENT_CONSULTATION REAL, "
               "LDB_INTRODUCTORY_PRACTICE REAL, "
               "LDB_PRE_DIPLOMA_PRACTICE REAL, "
               "LDB_COURSEWORK REAL, "
               "LDB_GUIDED_INDEPENDENT_WORK REAL, "
               "LDB_CONTROL_WORK REAL, "
               "LDB_GRADUATION_DESIGN REAL, "
               "LDB_GUIDE_GRADUATE REAL, "
               "LDB_STATE_EXAM REAL, "
               "LDB_HES REAL, "
               "LDB_GUIDE_CHAIR REAL, "
               "LDB_UIRS REAL, "
               "FOREIGN KEY(LDB_TCH_ID) REFERENCES DRT_TEACHERS(TCH_ID) ON DELETE CASCADE ON UPDATE CASCADE, "
               "FOREIGN KEY(LDB_LCL_ID) REFERENCES DRT_LOAD_CALCULATION(LCL_ID) ON DELETE CASCADE ON UPDATE CASCADE);");

    QString fields("LDB_TCH_ID,LDB_LCL_ID");

    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(1,1);");
    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(2,2);");
    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(3,3);");
    query.exec("INSERT INTO DRT_LOAD_DISTRIBUTION (" + fields + ") VALUES(3,4);");
}

void DbService::createLoadCalculationView() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE VIEW VIEW_LOAD_CALCULATION AS "
               "SELECT "
               "LCL.LCL_ID AS LCLV_ID, "
               "DSC.DSC_ID AS LCLV_DSC_ID, "
               "DSC.DSC_NAME as LCLV_DSC_NAME, "
               "VFLW.FLW_ID as LCLV_FLW_ID, "
               "VFLW.FLW_NAME as LCLV_FLW_NAME, "
               "DSC.DSC_LECTURES as LCLV_LECTURES, "
               "DSC.DSC_LABORATORY              * SUBGROUPS.SUBGROUPS_NUMBER as LCLV_LABORATORY, "
               "DSC.DSC_PRACTICAL as LCLV_PRACTICAL, "
               "DSC.DSC_CONSULTATION            * STUD.STUDENTS_NUMBER * FCT.FCT_CONSULTATION               as LCLV_CONSULTATION, "
               "DSC.DSC_EXAMINATIONS            * STUD.STUDENTS_NUMBER * FCT.FCT_EXAMINATIONS               as LCLV_EXAMINATIONS, "
               "DSC.DSC_TESTS                   * STUD.STUDENTS_NUMBER * FCT.FCT_TESTS                      as LCLV_TESTS, "
               "DSC.DSC_CURRENT_CONSULTATION    * STUD.STUDENTS_NUMBER * FCT.FCT_CURRENT_CONSULTATION       as LCLV_CURRENT_CONSULTATION, "
               "DSC.DSC_INTRODUCTORY_PRACTICE   * STUD.STUDENTS_NUMBER * FCT.FCT_INTRODUCTORY_PRACTICE      as LCLV_INTRODUCTORY_PRACTICE, "
               "DSC.DSC_PRE_DIPLOMA_PRACTICE    * STUD.STUDENTS_NUMBER * FCT.FCT_PRE_DIPLOMA_PRACTICE       as LCLV_PRE_DIPLOMA_PRACTICE, "
               "DSC.DSC_COURSEWORK              * STUD.STUDENTS_NUMBER * FCT.FCT_COURSEWORK                 as LCLV_COURSEWORK, "
               "DSC.DSC_GUIDED_INDEPENDENT_WORK * STUD.STUDENTS_NUMBER * FCT.FCT_GUIDED_INDEPENDENT_WORK    as LCLV_GUIDED_INDEPENDENT_WORK, "
               "DSC.DSC_CONTROL_WORK            * STUD.STUDENTS_NUMBER * FCT.FCT_CONTROL_WORK               as LCLV_CONTROL_WORK, "
               "DSC.DSC_GRADUATION_DESIGN       * STUD.STUDENTS_NUMBER * FCT.FCT_GRADUATION_DESIGN          as LCLV_GRADUATION_DESIGN, "
               "DSC.DSC_GUIDE_GRADUATE          * STUD.STUDENTS_NUMBER * FCT.FCT_GUIDE_GRADUATE             as LCLV_GUIDE_GRADUATE, "
               "DSC.DSC_STATE_EXAM              * STUD.STUDENTS_NUMBER * FCT.FCT_STATE_EXAM                 as LCLV_STATE_EXAM, "
               "DSC.DSC_HES                     * STUD.STUDENTS_NUMBER * FCT.FCT_HES                        as LCLV_HES, "
               "DSC.DSC_GUIDE_CHAIR             * STUD.STUDENTS_NUMBER * FCT.FCT_GUIDE_CHAIR                as LCLV_GUIDE_CHAIR, "
               "DSC.DSC_UIRS                    * STUD.STUDENTS_NUMBER * FCT.FCT_UIRS                       as LCLV_UIRS "
               "FROM DRT_FLOWS FLW, DRT_LOAD_CALCULATION LCL, DRT_DISCIPLINES DSC, VIEW_FLOWS VFLW, DRT_FACTORS FCT, DRT_GROUPS GRP, DRT_LINKS LNK "
               "JOIN (SELECT LNK.LNK_FLW_ID as FLW_ID, TOTAL(GRP.GRP_NUMBER_OF_STUDENTS) as STUDENTS_NUMBER FROM DRT_GROUPS GRP, DRT_LINKS LNK WHERE GRP.GRP_ID = LNK.LNK_GRP_ID GROUP BY LNK.LNK_FLW_ID) STUD ON STUD.FLW_ID = LCL.LCL_FLW_ID "
               "JOIN (SELECT LNK.LNK_FLW_ID as FLW_ID, TOTAL(GRP.GRP_NUMBER_OF_SUBGROUPS) as SUBGROUPS_NUMBER FROM DRT_GROUPS GRP, DRT_LINKS LNK WHERE GRP.GRP_ID = LNK.LNK_GRP_ID GROUP BY LNK.LNK_FLW_ID) SUBGROUPS ON SUBGROUPS.FLW_ID = LCL.LCL_FLW_ID "
               "WHERE LCL.LCL_FLW_ID = VFLW.FLW_ID "
               "AND LCL.LCL_DSC_ID = DSC.DSC_ID "
               "AND LCL.LCL_FLW_ID = FLW.FLW_ID "
               "AND FLW.FLW_ID = LNK.LNK_FLW_ID "
               "AND GRP.GRP_ID = LNK.LNK_GRP_ID "
               "AND FCT.FCT_ID = 1 "
               "GROUP BY LCL.LCL_ID");
}

void DbService::createLoadDistributionHelper() const
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.exec("CREATE VIEW VIEW_LOAD_DISTRIBUTION_HELPER AS "
               "SELECT "
               "LCL.LCL_ID AS LDH_ID, "
               "DSC.DSC_NAME || ' (' || VFLW.FLW_NAME || ')' as LDH_NAME "
               "FROM DRT_LOAD_CALCULATION LCL, DRT_DISCIPLINES DSC, VIEW_FLOWS VFLW "
               "WHERE LCL.LCL_FLW_ID = VFLW.FLW_ID "
               "AND LCL.LCL_DSC_ID = DSC.DSC_ID "
               "GROUP BY LCL.LCL_ID");
}

QStringList DbService::exportLcl()
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.prepare("SELECT "
                  "LCLV_DSC_NAME, LCLV_FLW_NAME, LCLV_LECTURES, LCLV_LABORATORY, LCLV_PRACTICAL, LCLV_CONSULTATION, "
                  "LCLV_EXAMINATIONS, LCLV_TESTS, LCLV_CURRENT_CONSULTATION, LCLV_INTRODUCTORY_PRACTICE, LCLV_PRE_DIPLOMA_PRACTICE, "
                  "LCLV_COURSEWORK, LCLV_GUIDED_INDEPENDENT_WORK, LCLV_CONTROL_WORK, LCLV_GRADUATION_DESIGN, LCLV_GUIDE_GRADUATE, "
                  "LCLV_STATE_EXAM, LCLV_HES, LCLV_GUIDE_CHAIR, LCLV_UIRS "
                  "FROM VIEW_LOAD_CALCULATION "
                  "ORDER BY LCLV_DSC_NAME, LCLV_FLW_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    QStringList result;

    while(query.next())
        result.append(toExportLclString(query.record()));

    return result;
}

QStringList DbService::exportLd()
{
    qDebug() << __FUNCTION__;

    QSqlQuery query;
    query.prepare("SELECT "
                  "TCH_NAME, LDH_NAME, LDB_LECTURES, LDB_LABORATORY, LDB_PRACTICAL, LDB_CONSULTATION, LDB_EXAMINATIONS, "
                  "LDB_TESTS, LDB_CURRENT_CONSULTATION, LDB_INTRODUCTORY_PRACTICE, LDB_PRE_DIPLOMA_PRACTICE, "
                  "LDB_COURSEWORK, LDB_GUIDED_INDEPENDENT_WORK, LDB_CONTROL_WORK, LDB_GRADUATION_DESIGN, "
                  "LDB_GUIDE_GRADUATE, LDB_STATE_EXAM, LDB_HES, LDB_GUIDE_CHAIR, LDB_UIRS "
                  "FROM DRT_LOAD_DISTRIBUTION LD "
                  "JOIN DRT_TEACHERS TCH ON TCH.TCH_ID = LD.LDB_TCH_ID "
                  "JOIN VIEW_LOAD_DISTRIBUTION_HELPER LDH ON LDH.LDH_ID = LD.LDB_LCL_ID "
                  "ORDER BY TCH_NAME, LDH_NAME");

    if (!query.exec())
        throw QString(query.lastError().text());

    QStringList result;

    while(query.next())
        result.append(toExportLdString(query.record()));

    return result;
}

QString DbService::toExportLclString(const QSqlRecord& record) const
{
    QString result;
    result += record.value("LCLV_DSC_NAME").toString() + " \t";
    result += record.value("LCLV_FLW_NAME").toString() + " \t";
    result += record.value("LCLV_LECTURES").toString() + " \t";
    result += record.value("LCLV_LABORATORY").toString() + " \t";
    result += record.value("LCLV_PRACTICAL").toString() + " \t";
    result += record.value("LCLV_CONSULTATION").toString() + " \t";
    result += record.value("LCLV_EXAMINATIONS").toString() + " \t";
    result += record.value("LCLV_TESTS").toString() + " \t";
    result += record.value("LCLV_CURRENT_CONSULTATION").toString() + " \t";
    result += record.value("LCLV_INTRODUCTORY_PRACTICE").toString() + " \t";
    result += record.value("LCLV_PRE_DIPLOMA_PRACTICE").toString() + " \t";
    result += record.value("LCLV_COURSEWORK").toString() + " \t";
    result += record.value("LCLV_GUIDED_INDEPENDENT_WORK").toString() + " \t";
    result += record.value("LCLV_CONTROL_WORK").toString() + " \t";
    result += record.value("LCLV_GRADUATION_DESIGN").toString() + " \t";
    result += record.value("LCLV_GUIDE_GRADUATE").toString() + " \t";
    result += record.value("LCLV_STATE_EXAM").toString() + " \t";
    result += record.value("LCLV_HES").toString() + " \t";
    result += record.value("LCLV_GUIDE_CHAIR").toString() + " \t";
    result += record.value("LCLV_UIRS").toString();

    return result;
}

QString DbService::toExportLdString(const QSqlRecord &record) const
{
    QString result;
    result += record.value("TCH_NAME").toString() + " \t";
    result += record.value("LDH_NAME").toString() + " \t";
    result += record.value("LDB_LECTURES").toString() + " \t";
    result += record.value("LDB_LABORATORY").toString() + " \t";
    result += record.value("LDB_PRACTICAL").toString() + " \t";
    result += record.value("LDB_CONSULTATION").toString() + " \t";
    result += record.value("LDB_EXAMINATIONS").toString() + " \t";
    result += record.value("LDB_TESTS").toString() + " \t";
    result += record.value("LDB_CURRENT_CONSULTATION").toString() + " \t";
    result += record.value("LDB_INTRODUCTORY_PRACTICE").toString() + " \t";
    result += record.value("LDB_PRE_DIPLOMA_PRACTICE").toString() + " \t";
    result += record.value("LDB_COURSEWORK").toString() + " \t";
    result += record.value("LDB_GUIDED_INDEPENDENT_WORK").toString() + " \t";
    result += record.value("LDB_CONTROL_WORK").toString() + " \t";
    result += record.value("LDB_GRADUATION_DESIGN").toString() + " \t";
    result += record.value("LDB_GUIDE_GRADUATE").toString() + " \t";
    result += record.value("LDB_STATE_EXAM").toString() + " \t";
    result += record.value("LDB_HES").toString() + " \t";
    result += record.value("LDB_GUIDE_CHAIR").toString() + " \t";
    result += record.value("LDB_UIRS").toString();

    return result;
}
