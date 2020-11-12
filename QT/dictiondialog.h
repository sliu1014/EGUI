#ifndef DICTIONDIALOG_H
#define DICTIONDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QInputDialog>
#include "schoolplannertablemodel.h"
#include <QListView>


namespace Ui {
class DictionDialog;
}

class DictionDialog : public QDialog
{
    Q_OBJECT

public:
    DictionDialog(QStringList &list, QWidget *parent = nullptr);
    ~DictionDialog();

private slots:


    void on_Add_clicked();

    void on_Remove_clicked();

    void on_Close_clicked();

private:
    Ui::DictionDialog *ui;
    QStringListModel *l_model;
    QStringList &list;
};

#endif // DICTIONDIALOG_H
