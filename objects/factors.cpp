#include "factors.h"

Factors::Factors() :
    _id(0)
  , _consultationFactor(0)
  , _examinationsFactor(0)
  , _testsFactor(0)
  , _currentConsultationFactor(0)
  , _introductoryPracticeFactor(0)
  , _preDiplomaPracticeFactor(0)
  , _courseWorkFactor(0)
  , _guideIndependentWorkFactor(0)
  , _controlWorkFactor(0)
  , _graduationDesignFactor(0)
  , _guideGraduateFactor(0)
  , _stateExamFactor(0)
  , _hesFactor(0)
  , _guideChairFactor(0)
  , _uirsFactor(0)
{

}

int Factors::getId() const
{
    return _id;
}

double Factors::getConsultationFactor() const
{
    return _consultationFactor;
}

double Factors::getExaminationFactor() const
{
    return _examinationsFactor;
}

double Factors::getTestsFactor() const
{
    return _testsFactor;
}

double Factors::getCurrentConsultationFactor() const
{
    return _currentConsultationFactor;
}

double Factors::getIntroductoryPracticeFactor() const
{
    return _introductoryPracticeFactor;
}

double Factors::getPreDiplomaPracticeFactor() const
{
    return _preDiplomaPracticeFactor;
}

double Factors::getCourseWorkFactor() const
{
    return _courseWorkFactor;
}

double Factors::getGuideIndependentWorkFactor() const
{
    return _guideIndependentWorkFactor;
}

double Factors::getControlWorkFactor() const
{
    return _controlWorkFactor;
}

double Factors::getGraduationDesignFactor() const
{
    return _graduationDesignFactor;
}

double Factors::getGuideGraduateFactor() const
{
    return _guideGraduateFactor;
}

double Factors::getStateExamFactor() const
{
    return _stateExamFactor;
}

double Factors::getHesFactor() const
{
    return _hesFactor;
}

double Factors::getGuideChairFactor() const
{
    return _guideChairFactor;
}

double Factors::getUirsFactor() const
{
    return _uirsFactor;
}

void Factors::setId(const int id)
{
    _id = id;
}

void Factors::setConsultationFactor(const double &consultationFactor)
{
    _consultationFactor = consultationFactor;
}

void Factors::setExaminationsFactor(const double &examinationsFactor)
{
    _examinationsFactor = examinationsFactor;
}

void Factors::setTestsFactor(const double &testsFactor)
{
    _testsFactor = testsFactor;
}

void Factors::setCurrentConsultationFactor(const double &currentConsultationFactor)
{
    _currentConsultationFactor = currentConsultationFactor;
}

void Factors::setIntroductoryPracticeFactor(const double &introductoryPracticeFactor)
{
    _introductoryPracticeFactor = introductoryPracticeFactor;
}

void Factors::setPreDiplomaPracticeFactor(const double &preDiplomaPracticeFactor)
{
    _preDiplomaPracticeFactor = preDiplomaPracticeFactor;
}

void Factors::setCourseWorkFactor(const double &courseWorkFactor)
{
    _courseWorkFactor = courseWorkFactor;
}

void Factors::setGuideIndependentWorkFactor(const double &guideIndependentWorkFactor)
{
    _guideIndependentWorkFactor = guideIndependentWorkFactor;
}

void Factors::setControlWorkFactor(const double &controlWorkFactor)
{
    _controlWorkFactor = controlWorkFactor;
}

void Factors::setGraduationDesignFactor(const double &graduationDesignFactor)
{
    _graduationDesignFactor = graduationDesignFactor;
}

void Factors::setGuideGraduateFactor(const double &guideGraduateFactor)
{
    _guideGraduateFactor = guideGraduateFactor;
}

void Factors::setStateExamFactor(const double &stateExamFactor)
{
    _stateExamFactor = stateExamFactor;
}

void Factors::setHesFactor(const double &hesFactor)
{
    _hesFactor = hesFactor;
}

void Factors::setGuideChairFactor(const double &guideChairFactor)
{
    _guideChairFactor = guideChairFactor;
}

void Factors::setUirsFactor(const double &uirsFactor)
{
    _uirsFactor = uirsFactor;
}
