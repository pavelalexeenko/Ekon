#ifndef TEACHER_H
#define TEACHER_H

#include <QString>

class Teacher
{
public:
    Teacher();
    Teacher(QString name, double rate, QString info);

    int getId() const;
    QString getName() const;
    double getRate() const;
    QString getInfo() const;

    void setId(const int& id);
    void setName(const QString& name);
    void setRate(const double& rate);
    void setInfo(const QString& info);

private:
    int _id;
    QString _name;
    double _rate;
    QString _info;
};

#endif // TEACHER_H
