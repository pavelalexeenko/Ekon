#ifndef LOADCALCULATION_H
#define LOADCALCULATION_H

#include <QString>

class LoadCalculation
{
public:
    LoadCalculation();

    int getId() const;
    int getFlowId() const;
    int getDisciplineId() const;

    void setId(const int id);
    void setFlowId(const int flowId);
    void setDisciplineId(const int disciplineId);

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
