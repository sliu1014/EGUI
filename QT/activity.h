#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QJsonObject>
#include <QString>

class Activity
{
public:

    QString Teacher;
    QString Course;
    QString Group;
    QString Room;

    quint16 DayOfWeek;
    quint16 TimeSlot;


    Activity(const QJsonObject &json);
    Activity(QString room, QString teacher, QString course, QString group, quint16 day, quint16 slot);
    Activity(const Activity &copy);

    void SaveData(QJsonObject &json)const;
    void LoadData(const QJsonObject &json);
    bool operator ==(const Activity &other) const;
};

#endif // ACTIVITY_H
