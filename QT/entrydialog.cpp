#include "entrydialog.h"
#include "ui_entrydialog.h"
#include <QDebug>

EntryDialog::EntryDialog(QWidget *parent, SchoolPlannerTableModel *model, quint16 day, quint16 slot) :
    QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);
    setWindowTitle("EntryDialog");
    r_model = model;
    dayOfWeek = day;
    timeSlot = slot;
    activityIndex = r_model->findActivity(day, slot);
    ui->room->setText(r_model->getActiveRoom());
    ui->class_2->setModel(new QStringListModel(r_model->Groups));
    ui->course->setModel(new QStringListModel(r_model->Courses));
    ui->teacher->setModel(new QStringListModel(r_model->Teachers));

    connect(ui->Unassign, &QPushButton::released, this, &EntryDialog::Unassign);

    if(activityIndex != -1)
    {
        auto activity = r_model->Activities[activityIndex];
        ui->class_2->setCurrentText(activity.Group);
        ui->course->setCurrentText(activity.Course);
        ui->teacher->setCurrentText(activity.Teacher);
    }

}

EntryDialog::~EntryDialog()
{
    delete ui;
}

QString EntryDialog::getRoom()
{
    return ui->room->text();
}

QString EntryDialog::getClass()
{
    return ui->class_2->currentText();
}

QString EntryDialog::getTeacher()
{
    return ui->teacher->currentText();
}

QString EntryDialog::getCourse()
{
    return ui->course->currentText();
}

void EntryDialog::on_Save_clicked()
{
    if(activityIndex == -1)
    {
        auto activity = Activity(getRoom(),getTeacher(),getCourse(),getClass(), dayOfWeek, timeSlot);
        r_model->Activities.append(activity);
    }else
    {
        auto activity = r_model->Activities[activityIndex];
        activity.Teacher = getTeacher();
        activity.Course = getCourse();
        activity.Group = getClass();
        r_model->Activities[activityIndex] = activity;
    }
    accept();
}

void EntryDialog::on_Cancel_clicked()
{
    close();
}

void EntryDialog::Unassign(void)
{
    r_model->Activities.removeAt(activityIndex);
    accept();
}

