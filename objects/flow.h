#ifndef FLOW_H
#define FLOW_H

#include <QString>
#include <QSet>

class Flow
{
public:
    Flow();

    int getId() const;
    QString getName() const;
    QString getNote() const;
    QSet<int> getGroupIds() const;

    void setId(const int& id);
    void setName(const QString& name);
    void setNote(const QString& note);
    void setGroupIds(const QSet<int>& groupIds);
    void addGroup(const int& id);
    void removeGroup(const int& id);

private:
    int _id;
    QString _name;
    QString _note;
    QSet<int> _groupIds;
};

#endif // FLOW_H
