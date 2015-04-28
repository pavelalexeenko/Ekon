#ifndef GROUP_H
#define GROUP_H

#include <QString>

class Group
{
public:
    Group();

    int getId() const;
    QString getName() const;
    int getNumberOfStudents() const;
    int getCourse() const;
    int getNumberOfSubgroups() const;
    int getSemestr() const;
    QString getFaculty() const;
    QString getSpeciality() const;
    QString getNote() const;

    void setId(const int& id);
    void setName(const QString& name);
    void setNumberOfStudents(const int& numberOfStudents);
    void setCourse(const int& course);
    void setNumberOfSubgroups(const int& numberOfSubGroups);
    void setSemestr(const int& semestr);
    void setFaculty(const QString& faculty);
    void setSpeciality(const QString& speciality);
    void setNote(const QString& note);

private:
    int _id;
    QString _name;
    int _numberOfStudents;
    int _course;
    int _numberOfSubgroups;
    int _semestr;
    QString _faculty;
    QString _speciality;
    QString _note;
};

#endif // GROUP_H
