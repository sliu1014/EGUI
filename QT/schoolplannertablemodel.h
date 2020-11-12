#ifndef SCHOOLPLANNERTABLEMODEL_H
#define SCHOOLPLANNERTABLEMODEL_H

#include <QAbstractTableModel>
#include "activity.h"

class SchoolPlannerTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

//    static const int TeacherNameRole = 0x0100;
//    static const int ClassNameRole = 0x0101;
//    static const int CourseNameRole = 0x0102;

    SchoolPlannerTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public:

    void save(const QString &filePath);
    void load(const QString &filePath);

    QString getActiveRoom(void) const;
    QString setActiveRoom(QString room);
    quint32 findActivity(quint16 day, quint16 slot);

    QList<Activity> Activities;
    QStringList Rooms;
    QStringList Groups;
    QStringList Courses;
    QStringList Teachers;


public slots:
    void Clear(void);

private:
    QString activeRoom;
};

#endif // SCHOOLPLANNERTABLEMODEL_H
