#ifndef TEACHER_H
#define TEACHER_H

#include <QString>

class Teacher
{
public:
    Teacher();
    Teacher(QString name, double rate, QString info);

    QString getName() const;
    double getRate() const;
    QString getInfo() const;

    void setName(const QString& name);
    void setRate(const double& rate);
    void setInfo(const QString& info);

private:
    QString _name;
    double _rate;
    QString _info;
};

#endif // TEACHER_H
