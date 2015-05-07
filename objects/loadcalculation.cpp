#include "loadcalculation.h"

LoadCalculation::LoadCalculation() :
    _id(0)
  , _flowId(0)
  , _disciplineId(0)
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
