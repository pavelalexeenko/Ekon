#include "flow.h"

Flow::Flow()
{
}

int Flow::getId() const
{
    return _id;
}

QString Flow::getName() const
{
    return _name;
}

QString Flow::getNote() const
{
    return _note;
}

QSet<int> Flow::getGroupIds() const
{
    return _groupIds;
}

void Flow::setId(const int &id)
{
    _id = id;
}

void Flow::setName(const QString &name)
{
    _name = name;
}

void Flow::setNote(const QString &note)
{
    _note = note;
}

void Flow::setGroupIds(const QSet<int> &groupIds)
{
    _groupIds = groupIds;
}

void Flow::addGroup(const int &id)
{
    _groupIds.insert(id);
}

void Flow::removeGroup(const int &id)
{
    _groupIds.remove(id);
}
