#include "teacher.h"

Teacher::Teacher() :
    _id(0)
  , _rate(0)
{
}

Teacher::Teacher(QString name, double rate, QString info):
    _name(name)
  , _rate(rate)
  , _info(info)
{
}

int Teacher::getId() const
{
    return _id;
}

QString Teacher::getName() const
{
    return _name;
}

double Teacher::getRate() const
{
    return _rate;
}

QString Teacher::getInfo() const
{
    return _info;
}

void Teacher::setId(const int &id)
{
    _id = id;
}

void Teacher::setName(const QString& name)
{
    _name = name;
}

void Teacher::setRate(const double& rate)
{
    _rate = rate;
}

void Teacher::setInfo(const QString& info)
{
    _info = info;
}
