#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <entrydialog.h>
#include <dictiondialog.h>
#include <QFileDialog>
#include <QJsonDocument>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("SchoolPlanner");
    model = new SchoolPlannerTableModel;
    RoomListModel = new QStringListModel(model->Rooms);
    ui->tableView->setModel(model);
    ui->rooms->setModel(RoomListModel);

    connect(ui->rooms, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::roomIndexChanged);
    connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::tableItemDoubleClicked);

    connect(ui->Action_open, &QAction::triggered, this, &MainWindow::loadData);
    connect(ui->Action_save, &QAction::triggered, this, &MainWindow::saveData);
    connect(ui->Action_quit, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->Action_room, &QAction::triggered, this, &MainWindow::editRooms);
    connect(ui->Action_class, &QAction::triggered, this, &MainWindow::editClasses);
    connect(ui->Action_course, &QAction::triggered, this, &MainWindow::editCourses);
    connect(ui->Action_teacher, &QAction::triggered, this, &MainWindow::editTeachers);

}

void MainWindow::tableItemDoubleClicked(const QModelIndex& index)
{
    EntryDialog dlg(this, model, index.column(), index.row());
    dlg.exec();
}

void MainWindow::roomIndexChanged(int index)
{
    if(index > -1 && index < model->Rooms.count())
    {
        auto room = model->Rooms.at(index);
        model->setActiveRoom(room);
    }else
    {
        model->setActiveRoom(QString());
    }
}

void MainWindow::editTeachers()
{
    DictionDialog dicEdit(model->Teachers, this);
    dicEdit.setWindowTitle("TeacherList");
    dicEdit.exec();
    RoomListModel->setStringList(model->Teachers);
}

void MainWindow::editCourses()
{
    DictionDialog dicEdit(model->Courses, this);
    dicEdit.setWindowTitle("CourseList");
    dicEdit.exec();
    RoomListModel->setStringList(model->Courses);
}

void MainWindow::editClasses()
{
    DictionDialog dicEdit(model->Groups, this);
    dicEdit.setWindowTitle("GroupList");
    dicEdit.exec();
    RoomListModel->setStringList(model->Groups);
}

void MainWindow::editRooms()
{
    DictionDialog dicEdit(model->Rooms, this);
    dicEdit.setWindowTitle("RoomList");
    dicEdit.exec();
    RoomListModel->setStringList(model->Rooms);
}

void MainWindow::loadData()
{
    auto fileName = QFileDialog::getOpenFileName(this);
    model->load(fileName);
    RoomListModel->setStringList(model->Rooms);
}

void MainWindow::saveData()
{
    auto fileName = QFileDialog::getSaveFileName(this);
    model->save(fileName);
}

void MainWindow::quit()
{
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}


