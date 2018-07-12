#ifndef LOADCALCULATION_H
#define LOADCALCULATION_H

class LoadCalculation
{
public:
    LoadCalculation();

    int getId() const;
    int getFlowId() const;
    int getDisciplineId() const;
    double getLectures() const;
    double getLaboratory() const;
    double getPractical() const;
    double getConsultation() const;
    double getExamination() const;
    double getTests() const;
    double getCurrentConsultation() const;
    double getIntroductoryPractice() const;
    double getPreDiplomaPractice() const;
    double getCourseWork() const;
    double getGuideIndependentWork() const;
    double getControlWork() const;
    double getGraduationDesign() const;
    double getGuideGraduate() const;
    double getStateExam() const;
    double getHes() const;
    double getGuideChair() const;
    double getUirs() const;

    void setId(const int id);
    void setFlowId(const int flowId);
    void setDisciplineId(const int disciplineId);
    void setLectures(const double& lectures);
    void setLaboratory(const double& laboratory);
    void setPractical(const double& practical);
    void setConsultation(const double& consultation);
    void setExaminations(const double& examinations);
    void setTests(const double& tests);
    void setCurrentConsultation(const double& currentConsultation);
    void setIntroductoryPractice(const double& introductoryPractice);
    void setPreDiplomaPractice(const double& preDiplomaPractice);
    void setCourseWork(const double& courseWork);
    void setGuideIndependentWork(const double& guideIndependentWork);
    void setControlWork(const double& controlWork);
    void setGraduationDesign(const double& graduationDesign);
    void setGuideGraduate(const double& guideGraduate);
    void setStateExam(const double& stateExam);
    void setHes(const double& hes);
    void setGuideChair(const double& guideChair);
    void setUirs(const double& uirs);

private:
    int _id;
    int _flowId;
    int _disciplineId;

    double _lectures;
    double _laboratory;
    double _practical;
    double _consultation;
    double _examinations;
    double _tests;
    double _currentConsultation;
    double _introductoryPractice;
    double _preDiplomaPractice;
    double _courseWork;
    double _guideIndependentWork;
    double _controlWork;
    double _graduationDesign;
    double _guideGraduate;
    double _stateExam;
    double _hes;
    double _guideChair;
    double _uirs;
};

#endif // LOADCALCULATION_H
