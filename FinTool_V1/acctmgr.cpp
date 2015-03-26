#include "acctmgr.h"
#include "ui_acctmgr.h"
#include "QStandardItemModel"
#include <QFile>
AcctMgr::AcctMgr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AcctMgr)
{
    ui->setupUi(this);

    //Change tab name
    ui->tabWidget->setTabText(0, "Account 1");

    //Create columns and rows
    QStandardItemModel *model = new QStandardItemModel(2,3,this); //2 rows and 3 columns

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("column1 Header")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2 Header")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));

    QStandardItem *firstRow = new QStandardItem(QString("ColumnValue"));
    model->setItem(0,0,firstRow);

    ui->tableView->setModel(model);
}


AcctMgr::~AcctMgr()
{
    delete ui;
}

