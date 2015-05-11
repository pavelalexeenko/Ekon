#include "loadcalculation.h"

LoadCalculation::LoadCalculation() :
    _id(0)
  , _flowId(0)
  , _disciplineId(0)
  , _lectures(0)
  , _laboratory(0)
  , _practical(0)
  , _consultation(0)
  , _examinations(0)
  , _tests(0)
  , _currentConsultation(0)
  , _introductoryPractice(0)
  , _preDiplomaPractice(0)
  , _courseWork(0)
  , _guideIndependentWork(0)
  , _controlWork(0)
  , _graduationDesign(0)
  , _guideGraduate(0)
  , _stateExam(0)
  , _hes(0)
  , _guideChair(0)
  , _uirs(0)
{
}

int LoadCalculation::getId() const
{
    return _id;
}

int LoadCalculation::getFlowId() const
{
    return _flowId;
}

int LoadCalculation::getDisciplineId() const
{
    return _disciplineId;
}

double LoadCalculation::getLectures() const
{
    return _lectures;
}

double LoadCalculation::getLaboratory() const
{
    return _laboratory;
}

double LoadCalculation::getPractical() const
{
    return _practical;
}

double LoadCalculation::getConsultation() const
{
    return _consultation;
}

double LoadCalculation::getExamination() const
{
    return _examinations;
}

double LoadCalculation::getTests() const
{
    return _tests;
}

double LoadCalculation::getCurrentConsultation() const
{
    return _currentConsultation;
}

double LoadCalculation::getIntroductoryPractice() const
{
    return _introductoryPractice;
}

double LoadCalculation::getPreDiplomaPractice() const
{
    return _preDiplomaPractice;
}

double LoadCalculation::getCourseWork() const
{
    return _courseWork;
}

double LoadCalculation::getGuideIndependentWork() const
{
    return _guideIndependentWork;
}

double LoadCalculation::getControlWork() const
{
    return _controlWork;
}

double LoadCalculation::getGraduationDesign() const
{
    return _graduationDesign;
}

double LoadCalculation::getGuideGraduate() const
{
    return _guideGraduate;
}

double LoadCalculation::getStateExam() const
{
    return _stateExam;
}

double LoadCalculation::getHes() const
{
    return _hes;
}

double LoadCalculation::getGuideChair() const
{
    return _guideChair;
}

double LoadCalculation::getUirs() const
{
    return _uirs;
}

void LoadCalculation::setId(const int id)
{
    _id = id;
}

void LoadCalculation::setFlowId(const int flowId)
{
    _flowId = flowId;
}

void LoadCalculation::setDisciplineId(const int disciplineId)
{
    _disciplineId = disciplineId;
}

void LoadCalculation::setLectures(const double &lectures)
{
    _lectures = lectures;
}

void LoadCalculation::setLaboratory(const double &laboratory)
{
    _laboratory = laboratory;
}

void LoadCalculation::setPractical(const double &practical)
{
    _practical = practical;
}

void LoadCalculation::setConsultation(const double &consultation)
{
    _consultation = consultation;
}

void LoadCalculation::setExaminations(const double &examinations)
{
    _examinations = examinations;
}

void LoadCalculation::setTests(const double &tests)
{
    _tests = tests;
}

void LoadCalculation::setCurrentConsultation(const double &currentConsultation)
{
    _currentConsultation = currentConsultation;
}

void LoadCalculation::setIntroductoryPractice(const double &introductoryPractice)
{
    _introductoryPractice = introductoryPractice;
}

void LoadCalculation::setPreDiplomaPractice(const double &preDiplomaPractice)
{
    _preDiplomaPractice = preDiplomaPractice;
}

void LoadCalculation::setCourseWork(const double &courseWork)
{
    _courseWork = courseWork;
}

void LoadCalculation::setGuideIndependentWork(const double &guideIndependentWork)
{
    _guideIndependentWork = guideIndependentWork;
}

void LoadCalculation::setControlWork(const double &controlWork)
{
    _controlWork = controlWork;
}

void LoadCalculation::setGraduationDesign(const double &graduationDesign)
{
    _graduationDesign = graduationDesign;
}

void LoadCalculation::setGuideGraduate(const double &guideGraduate)
{
    _guideGraduate = guideGraduate;
}

void LoadCalculation::setStateExam(const double &stateExam)
{
    _stateExam = stateExam;
}

void LoadCalculation::setHes(const double &hes)
{
    _hes = hes;
}

void LoadCalculation::setGuideChair(const double &guideChair)
{
    _guideChair = guideChair;
}

void LoadCalculation::setUirs(const double &uirs)
{
    _uirs = uirs;
}
