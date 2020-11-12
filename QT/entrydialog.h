#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>
#include <schoolplannertablemodel.h>
#include <QStringListModel>

namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    EntryDialog(QWidget *parent = nullptr,SchoolPlannerTableModel *model = nullptr, quint16 day = 0, quint16 slot = 0);
    ~EntryDialog();

    QString getRoom();
    QString getClass();
    QString getCourse();
    QString getTeacher();

private slots:
    void on_Save_clicked();

    void on_Cancel_clicked();

    void Unassign(void);


private:
    Ui::EntryDialog *ui;
    SchoolPlannerTableModel *r_model;
    qint32 activityIndex;
    quint16 dayOfWeek;
    quint16 timeSlot;
};

#endif // ENTRYDIALOG_H
