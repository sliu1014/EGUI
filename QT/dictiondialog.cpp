#include "dictiondialog.h"
#include "ui_dictiondialog.h"

DictionDialog::DictionDialog(QStringList &list,QWidget *parent) :
    QDialog(parent),list(list),
    ui(new Ui::DictionDialog)
{
    ui->setupUi(this);
    l_model = new QStringListModel(this);
    l_model->setStringList(list);
    ui->listView->setModel(l_model);

    connect(ui->Add, &QPushButton::clicked, this, &DictionDialog::on_Add_clicked);
    connect(ui->Remove, &QPushButton::clicked, this, &DictionDialog::on_Remove_clicked);
    connect(ui->Close, &QPushButton::clicked, this, &DictionDialog::on_Close_clicked);

}

DictionDialog::~DictionDialog()
{
    delete ui;
}



void DictionDialog::on_Add_clicked()
{
    bool check;
    QString str = QInputDialog::getText(this, tr("Add Dictionary"), tr("Value:"), QLineEdit::Normal, tr(""), &check);
    if(check && !str.isEmpty())
    {
        list.append(str);
        l_model->setStringList(list);
    }
}

void DictionDialog::on_Remove_clicked()
{
    auto str = ui->listView->selectionModel()->selectedIndexes();
    for(auto iter = str.begin(); iter != str.end(); iter++)
    {
        list.removeAt(iter->row());
    }
    l_model->setStringList(list);
}

void DictionDialog::on_Close_clicked()
{
    close();
}
