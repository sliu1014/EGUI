#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <schoolplannertablemodel.h>
#include <QStringListModel>


namespace Ui { class MainWindow; }
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadData();
    void saveData();
    void quit();
    void editRooms();
    void editClasses();
    void editCourses();
    void editTeachers();
    void roomIndexChanged(int index);
    void tableItemDoubleClicked(const QModelIndex& index);

private:
    Ui::MainWindow *ui;
    SchoolPlannerTableModel *model;
    QStringListModel *RoomListModel;
};

#endif // MAINWINDOW_H
