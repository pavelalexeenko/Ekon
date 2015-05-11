#include "discipline.h"

Discipline::Discipline() :
    _id(0)
  , _lectures(0)
  , _laboratory(0)
  , _practical(0)
  , _consultation(false)
  , _examinations(false)
  , _tests(false)
  , _currentConsultation(false)
  , _introductoryPractice(false)
  , _preDiplomaPractice(false)
  , _courseWork(false)
  , _guidedIndependentWork(false)
  , _controlWork(false)
  , _graduationDesign(false)
  , _guideGraduate(false)
  , _stateExam(false)
  , _hes(false)
  , _guideChair(false)
  , _uirs(false)
{

}

int Discipline::getId() const
{
    return _id;
}

QString Discipline::getName() const
{
    return _name;
}

double Discipline::getLectures() const
{
    return _lectures;
}

double Discipline::getLaboratory() const
{
    return _laboratory;
}

double Discipline::getPractical() const
{
    return _practical;
}

bool Discipline::hasConsultation() const
{
    return _consultation;
}

bool Discipline::hasExamination() const
{
    return _examinations;
}

bool Discipline::hasTests() const
{
    return _tests;
}

bool Discipline::hasCurrentConsultation() const
{
    return _currentConsultation;
}

bool Discipline::hasIntroductoryPractice() const
{
    return _introductoryPractice;
}

bool Discipline::hasPreDiplomaPractice() const
{
    return _preDiplomaPractice;
}

bool Discipline::hasCourseWork() const
{
    return _courseWork;
}

bool Discipline::hasGuidedIndependentWork() const
{
    return _guidedIndependentWork;
}

bool Discipline::hasControlWork() const
{
    return _controlWork;
}

bool Discipline::hasGraduationDesign() const
{
    return _graduationDesign;
}

bool Discipline::hasGuideGraduate() const
{
    return _guideGraduate;
}

bool Discipline::hasStateExam() const
{
    return _stateExam;
}

bool Discipline::hasHes() const
{
    return _hes;
}

bool Discipline::hasGuideChair() const
{
    return _guideChair;
}

bool Discipline::hasUirs() const
{
    return _uirs;
}

void Discipline::setId(const int &id)
{
    _id = id;
}

void Discipline::setName(const QString &name)
{
    _name = name;
}

void Discipline::setLectures(const double &lectures)
{
    _lectures = lectures;
}

void Discipline::setLaboratory(const double &laboratory)
{
    _laboratory = laboratory;
}

void Discipline::setPractical(const double &practical)
{
    _practical = practical;
}

void Discipline::setConsultation(const bool &consultation)
{
    _consultation = consultation;
}

void Discipline::setExaminations(const bool &examinations)
{
    _examinations = examinations;
}

void Discipline::setTests(const bool &tests)
{
    _tests = tests;
}

void Discipline::setCurrentConsultation(const bool &currentConsultation)
{
    _currentConsultation = currentConsultation;
}

void Discipline::setIntroductoryPractice(const bool &introductoryPractice)
{
    _introductoryPractice = introductoryPractice;
}

void Discipline::setPreDiplomaPractice(const bool &preDiplomaPractice)
{
    _preDiplomaPractice = preDiplomaPractice;
}

void Discipline::setCourseWork(const bool &courseWork)
{
    _courseWork = courseWork;
}

void Discipline::setGuidedIndependentWork(const bool &guidedIndependentWork)
{
    _guidedIndependentWork = guidedIndependentWork;
}

void Discipline::setControlWork(const bool &controlWork)
{
    _controlWork = controlWork;
}

void Discipline::setGraduationDesign(const bool &graduationDesign)
{
    _graduationDesign = graduationDesign;
}

void Discipline::setGuideGraduate(const bool &guideGraduate)
{
    _guideGraduate = guideGraduate;
}

void Discipline::setStateExam(const bool &stateExam)
{
    _stateExam = stateExam;
}

void Discipline::setHes(const bool &hes)
{
    _hes = hes;
}

void Discipline::setGuideChair(const bool &guideChair)
{
    _guideChair = guideChair;
}

void Discipline::setUirs(const bool &uirs)
{
    _uirs = uirs;
}
