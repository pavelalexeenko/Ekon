#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <QString>

class Discipline
{
public:
    Discipline();

    QString getName() const;
    double getLectures() const;
    double getLaboratory() const;
    double getPractical() const;
    bool hasConsultation() const;
    bool hasExamination() const;
    bool hasTests() const;
    bool hasCurrentConsultation() const;
    bool hasIntroductoryPractice() const;
    bool hasPreDiplomaPractice() const;
    bool hasCourseWork() const;
    bool hasGuideIndependentWork() const;
    bool hasControlWork() const;
    bool hasGraduationDesign() const;
    bool hasGuideGraduate() const;
    bool hasStateExam() const;
    bool hasHes() const;
    bool hasGuideChair() const;
    bool hasUirs() const;

    void setName(const QString& name);
    void setLectures(const double& lectures);
    void setLaboratory(const double& laboratory);
    void setPractical(const double& practical);
    void setConsultation(const bool& consultation);
    void setExaminations(const bool& examinations);
    void setTests(const bool& tests);
    void setCurrentConsultation(const bool& currentConsultation);
    void setIntroductoryPractice(const bool& introductoryPractice);
    void setPreDiplomaPractice(const bool& preDiplomaPractice);
    void setCourseWork(const bool& courseWork);
    void setGuideIndependentWork(const bool& guideIndependentWork);
    void setControlWork(const bool& controlWork);
    void setGraduationDesign(const bool& graduationDesign);
    void setGuideGraduate(const bool& guideGraduate);
    void setStateExam(const bool& stateExam);
    void setHes(const bool& hes);
    void setGuideChair(const bool& guideChair);
    void setUirs(const bool& uirs);

private:
    QString _name;
    double _lectures;
    double _laboratory;
    double _practical;
    bool _consultation;
    bool _examinations;
    bool _tests;
    bool _currentConsultation;
    bool _introductoryPractice;
    bool _preDiplomaPractice;
    bool _courseWork;
    bool _guideIndependentWork;
    bool _controlWork;
    bool _graduationDesign;
    bool _guideGraduate;
    bool _stateExam;
    bool _hes;
    bool _guideChair;
    bool _uirs;
};

#endif // DISCIPLINE_H
