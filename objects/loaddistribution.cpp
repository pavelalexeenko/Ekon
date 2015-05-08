#include "loaddistribution.h"

LoadDistribution::LoadDistribution()
{

}

int LoadDistribution::getId() const
{
    return _id;
}

int LoadDistribution::getLoadCalculaionId() const
{
    return _loadCalculaionId;
}

int LoadDistribution::getTeacherId() const
{
    return _teacherId;
}

double LoadDistribution::getLectures() const
{
    return _lectures;
}

double LoadDistribution::getLaboratory() const
{
    return _laboratory;
}

double LoadDistribution::getPractical() const
{
    return _practical;
}

double LoadDistribution::getConsultation() const
{
    return _consultation;
}

double LoadDistribution::getExamination() const
{
    return _examinations;
}

double LoadDistribution::getTests() const
{
    return _tests;
}

double LoadDistribution::getCurrentConsultation() const
{
    return _currentConsultation;
}

double LoadDistribution::getIntroductoryPractice() const
{
    return _introductoryPractice;
}

double LoadDistribution::getPreDiplomaPractice() const
{
    return _preDiplomaPractice;
}

double LoadDistribution::getCourseWork() const
{
    return _courseWork;
}

double LoadDistribution::getGuideIndependentWork() const
{
    return _guideIndependentWork;
}

double LoadDistribution::getControlWork() const
{
    return _controlWork;
}

double LoadDistribution::getGraduationDesign() const
{
    return _graduationDesign;
}

double LoadDistribution::getGuideGraduate() const
{
    return _guideGraduate;
}

double LoadDistribution::getStateExam() const
{
    return _stateExam;
}

double LoadDistribution::getHes() const
{
    return _hes;
}

double LoadDistribution::getGuideChair() const
{
    return _guideChair;
}

double LoadDistribution::getUirs() const
{
    return _uirs;
}

void LoadDistribution::setId(const int id)
{
    _id = id;
}

void LoadDistribution::setLoadCalculaionId(const int loadCalculaionId)
{
    _loadCalculaionId = loadCalculaionId;
}

void LoadDistribution::setTeacherId(const int teacherId)
{
    _teacherId = teacherId;
}

void LoadDistribution::setLectures(const double &lectures)
{
    _lectures = lectures;
}

void LoadDistribution::setLaboratory(const double &laboratory)
{
    _laboratory = laboratory;
}

void LoadDistribution::setPractical(const double &practical)
{
    _practical = practical;
}

void LoadDistribution::setConsultation(const double &consultation)
{
    _consultation = consultation;
}

void LoadDistribution::setExaminations(const double &examinations)
{
    _examinations = examinations;
}

void LoadDistribution::setTests(const double &tests)
{
    _tests = tests;
}

void LoadDistribution::setCurrentConsultation(const double &currentConsultation)
{
    _currentConsultation = currentConsultation;
}

void LoadDistribution::setIntroductoryPractice(const double &introductoryPractice)
{
    _introductoryPractice = introductoryPractice;
}

void LoadDistribution::setPreDiplomaPractice(const double &preDiplomaPractice)
{
    _preDiplomaPractice = preDiplomaPractice;
}

void LoadDistribution::setCourseWork(const double &courseWork)
{
    _courseWork = courseWork;
}

void LoadDistribution::setGuideIndependentWork(const double &guideIndependentWork)
{
    _guideIndependentWork = guideIndependentWork;
}

void LoadDistribution::setControlWork(const double &controlWork)
{
    _controlWork = controlWork;
}

void LoadDistribution::setGraduationDesign(const double &graduationDesign)
{
    _graduationDesign = graduationDesign;
}

void LoadDistribution::setGuideGraduate(const double &guideGraduate)
{
    _guideGraduate = guideGraduate;
}

void LoadDistribution::setStateExam(const double &stateExam)
{
    _stateExam = stateExam;
}

void LoadDistribution::setHes(const double &hes)
{
    _hes = hes;
}

void LoadDistribution::setGuideChair(const double &guideChair)
{
    _guideChair = guideChair;
}

void LoadDistribution::setUirs(const double &uirs)
{
    _uirs = uirs;
}
