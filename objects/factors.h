#ifndef FACTORS_H
#define FACTORS_H


class Factors
{
public:
    Factors();

    int getId() const;
    double getConsultationFactor() const;
    double getExaminationFactor() const;
    double getTestsFactor() const;
    double getCurrentConsultationFactor() const;
    double getIntroductoryPracticeFactor() const;
    double getPreDiplomaPracticeFactor() const;
    double getCourseWorkFactor() const;
    double getGuideIndependentWorkFactor() const;
    double getControlWorkFactor() const;
    double getGraduationDesignFactor() const;
    double getGuideGraduateFactor() const;
    double getStateExamFactor() const;
    double getHesFactor() const;
    double getGuideChairFactor() const;
    double getUirsFactor() const;

    void setId(const int id);
    void setConsultationFactor(const double& consultationFactor);
    void setExaminationsFactor(const double& examinationsFactor);
    void setTestsFactor(const double& testsFactor);
    void setCurrentConsultationFactor(const double& currentConsultationFactor);
    void setIntroductoryPracticeFactor(const double& introductoryPracticeFactor);
    void setPreDiplomaPracticeFactor(const double& preDiplomaPracticeFactor);
    void setCourseWorkFactor(const double& courseWorkFactor);
    void setGuideIndependentWorkFactor(const double& guideIndependentWorkFactor);
    void setControlWorkFactor(const double& controlWorkFactor);
    void setGraduationDesignFactor(const double& graduationDesignFactor);
    void setGuideGraduateFactor(const double& guideGraduateFactor);
    void setStateExamFactor(const double& stateExamFactor);
    void setHesFactor(const double& hesFactor);
    void setGuideChairFactor(const double& guideChairFactor);
    void setUirsFactor(const double& uirsFactor);

private:
    int _id;
    double _consultationFactor;
    double _examinationsFactor;
    double _testsFactor;
    double _currentConsultationFactor;
    double _introductoryPracticeFactor;
    double _preDiplomaPracticeFactor;
    double _courseWorkFactor;
    double _guideIndependentWorkFactor;
    double _controlWorkFactor;
    double _graduationDesignFactor;
    double _guideGraduateFactor;
    double _stateExamFactor;
    double _hesFactor;
    double _guideChairFactor;
    double _uirsFactor;
};

#endif // FACTORS_H
