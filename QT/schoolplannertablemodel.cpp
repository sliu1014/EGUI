#include "schoolplannertablemodel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

const int COLUMN_COUNT = 5;
const int ROW_COUNT = 9;

SchoolPlannerTableModel::SchoolPlannerTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    Courses.append(tr("mat"));
    Courses.append(tr("eng"));
    Courses.append(tr("phy"));
    Courses.append(tr("cs"));
    Courses.append(tr("geo"));
    Courses.append(tr("wir"));

    Rooms.append(tr("120"));
    Rooms.append(tr("121"));
    Rooms.append(tr("122"));
    Rooms.append(tr("123"));

    Teachers.append(tr("John"));
    Teachers.append(tr("Doe"));
    Teachers.append(tr("Marek"));
    Teachers.append(tr("Joe"));
    Teachers.append(tr("David"));
    Teachers.append(tr("shui"));

    Groups.append(tr("1a"));
    Groups.append(tr("1b"));
    Groups.append(tr("1c"));
    Groups.append(tr("2a"));
    Groups.append(tr("2b"));
    Groups.append(tr("2c"));

    setActiveRoom(tr("120"));

}

QVariant SchoolPlannerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    // FIXME: Implement me!
    static QList<QString> headers = {"Mon","Tue","Wed","Th","Fri"};
    static QList<QString> headerL = {"08:00-08:45",
                                     "08:55-09:40",
                                     "09:50-11:35",
                                     "11:55-12:40",
                                     "12:50-13:35",
                                     "13:45-14:30",
                                     "14:40-15:25",
                                     "15:35-16:20",
                                     "16:30-17:15"};
    if(orientation == Qt::Vertical)
    {
        if(role == Qt::DisplayRole)
        {
            return headerL[section];
        }
    }else {
        if(role == Qt::DisplayRole)
        {
            return headers[section];
        }
}
    return QVariant();
}

int SchoolPlannerTableModel::rowCount(const QModelIndex &parent) const
{
//    if (parent.isValid())
//        return 0;

    // FIXME: Implement me!
    Q_UNUSED(parent);
    return ROW_COUNT;
}

int SchoolPlannerTableModel::columnCount(const QModelIndex &parent) const
{
//    if (parent.isValid())
//        return 0;

    // FIXME: Implement me!
    Q_UNUSED(parent);
    return COLUMN_COUNT;
}

Qt::ItemFlags SchoolPlannerTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


QVariant SchoolPlannerTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if(role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignCenter);
    }

    auto timeSlot = index.row();
    auto dayOfWeek = index.column();

    if(role == Qt::DisplayRole)
    {
        for(auto iter = Activities.begin(); iter != Activities.end(); ++iter)
        {
            if(iter->Room == activeRoom && iter->DayOfWeek == dayOfWeek && iter->TimeSlot == timeSlot)
            {
                return iter->Group;
            }
        }
    }

    return QVariant();
}

void SchoolPlannerTableModel::load(const QString &filePath)
{

    Clear();
    QFile loadFile(filePath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Couldn't open file";
    }

    auto saveData = loadFile.readAll();
    auto jsonDocument = QJsonDocument::fromJson(saveData);
    loadFile.close();

    QJsonArray JsonRooms = jsonDocument["rooms"].toArray();
    QJsonArray JsonGroups = jsonDocument["groups"].toArray();
    QJsonArray JsonCourse = jsonDocument["courses"].toArray();
    QJsonArray JsonTeachers = jsonDocument["teachers"].toArray();
    QJsonArray JsonActvities = jsonDocument["activities"].toArray();

    for(const QJsonValue &value : JsonRooms)
    {
        Rooms.append(value.toString());
    }
    for(const QJsonValue &value : JsonGroups)
    {
        Groups.append(value.toString());
    }
    for(const QJsonValue &value : JsonCourse)
    {
        Courses.append(value.toString());
    }
    for(const QJsonValue &value : JsonTeachers)
    {
        Teachers.append(value.toString());
    }

    for(const QJsonValue &value : JsonActvities)
    {
        auto jsonObject = value.toObject();
        Activity activity(jsonObject);
        Activities.append(activity);
    }

    if(Rooms.count() > 0)
    {
        setActiveRoom(Rooms[0]);
    }

}

void SchoolPlannerTableModel::save(const QString &filePath)
{
    QFile saveToFile(filePath);
    if(!saveToFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Couldn't open save file.";
    }

    QJsonObject jsonRoot;
    QJsonArray jsonRooms;
    QJsonArray jsonGroups;
    QJsonArray jsonCourses;
    QJsonArray jsonTeachers;
    QJsonArray jsonActivities;

    for(const QString &value : Rooms)
    {
        jsonRooms.append(value);
    }
    for(const QString &value : Groups)
    {
        jsonGroups.append(value);
    }
    for(const QString &value : Courses)
    {
        jsonCourses.append(value);
    }
    for(const QString &value : Teachers)
    {
        jsonTeachers.append(value);
    }
    for(const Activity &value : Activities)
    {
        QJsonObject jsonValue;
        value.SaveData(jsonValue);
        jsonActivities.append(jsonValue);
    }

    jsonRoot["rooms"] = jsonRooms;
    jsonRoot["groups"] = jsonGroups;
    jsonRoot["courses"] = jsonCourses;
    jsonRoot["teachers"] = jsonTeachers;
    jsonRoot["activities"] = jsonActivities;

    saveToFile.write(QJsonDocument(jsonRoot).toJson());
    saveToFile.close();
}

QString SchoolPlannerTableModel::getActiveRoom() const
{
    return activeRoom;
}

QString SchoolPlannerTableModel::setActiveRoom(QString room)
{
    auto ActiveRoom = activeRoom;
    activeRoom = room;
    emit dataChanged(index(0,0), index(8,4), QVector<int>());
    return ActiveRoom;
}

quint32 SchoolPlannerTableModel::findActivity(quint16 day, quint16 slot)
{
    for(auto i = Activities.count() - 1; i >= 0; i--)
    {
        auto iter = Activities[i];
        if(iter.Room == activeRoom && iter.DayOfWeek == day && iter.TimeSlot == slot)
        {
            return i;
        }
    }

    return -1;
}

void SchoolPlannerTableModel::Clear(void)
{
    setActiveRoom(QString());
    Activities.clear();
    Rooms.clear();
    Groups.clear();
    Courses.clear();
    Teachers.clear();
}
