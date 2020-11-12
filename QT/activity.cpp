#include "activity.h"

Activity::Activity(QString room, QString teacher, QString course, QString group, quint16 day, quint16 slot)
{
    Teacher = teacher;
    Course = course;
    Group = group;
    Room = room;
    DayOfWeek = day;
    TimeSlot = slot;
}

Activity::Activity(const Activity &copy)
{
    Teacher = copy.Teacher;
    Course = copy.Course;
    Group = copy.Group;
    Room = copy.Room;
    DayOfWeek = copy.DayOfWeek;
    TimeSlot = copy.TimeSlot;
}

Activity::Activity(const QJsonObject &json)
{
    LoadData(json);
}

void Activity::SaveData(QJsonObject &json)const
{
    json["teacher"] = Teacher;
    json["course"] = Course;
    json["group"] = Group;
    json["room"] = Room;
    json["slot"] = TimeSlot;
    json["day"] = DayOfWeek;
}

void Activity::LoadData(const QJsonObject &json)
{
    Teacher = json["teacher"].toString();
    Course = json["course"].toString();
    Group = json["group"].toString();
    Room = json["room"].toString();
    TimeSlot = json["slot"].toInt();

    DayOfWeek = json["day"].toInt();


}

bool Activity::operator==(const Activity &other)const
{
    return Teacher == other.Teacher
        && Course == other.Course
        && Group == other.Group
        && Room == other.Room
        && DayOfWeek == other.DayOfWeek
        && TimeSlot == other.TimeSlot;
}
