#include "group.h"

Group::Group() :
    _id(0)
  , _numberOfStudents(0)
  , _course(0)
  , _numberOfSubgroups(0)
  , _semestr(0)
{
}

int Group::getId() const
{
    return _id;
}

QString Group::getName() const
{
    return _name;
}

int Group::getNumberOfStudents() const
{
    return _numberOfStudents;
}

int Group::getCourse() const
{
    return _course;
}

int Group::getNumberOfSubgroups() const
{
    return _numberOfSubgroups;
}

int Group::getSemestr() const
{
    return _semestr;
}

QString Group::getFaculty() const
{
    return _faculty;
}

QString Group::getSpeciality() const
{
    return _speciality;
}

QString Group::getNote() const
{
    return _note;
}

void Group::setId(const int &id)
{
    _id = id;
}

void Group::setName(const QString &name)
{
    _name = name;
}

void Group::setNumberOfStudents(const int &numberOfStudents)
{
    _numberOfStudents = numberOfStudents;
}

void Group::setCourse(const int &course)
{
    _course = course;
}

void Group::setNumberOfSubgroups(const int &numberOfSubGroups)
{
    _numberOfSubgroups = numberOfSubGroups;
}

void Group::setSemestr(const int &semestr)
{
    _semestr = semestr;
}

void Group::setFaculty(const QString &faculty)
{
    _faculty = faculty;
}

void Group::setSpeciality(const QString &speciality)
{
    _speciality = speciality;
}

void Group::setNote(const QString &note)
{
    _note = note;
}
