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
    ui->tabWidget->setTabText(0, "cash");

    //Create columns and rows
    QStandardItemModel *model = new QStandardItemModel(10,6,this); //10 rows and 6 columns


    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Date")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Type")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Category")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Payee")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Amount")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Balance")));

    loadInitAcct(model);

    ui->tableView->setModel(model);
}


AcctMgr::~AcctMgr()
{
    delete ui;
}


void AcctMgr::on_pushButton_2_clicked()
{
    addTrans = new addNewTransaction();
    addTrans->show();
}

void AcctMgr::loadInitAcct(QStandardItemModel *model){
    QFile fp("cash.txt");
    int i = 0, j = 0;

    if(!fp.open(QIODevice::ReadOnly)){
        qDebug() << fp.errorString();
    }

    QTextStream in(&fp);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList wordList;
        wordList.append(line.split(','));
        foreach(QString s, wordList){
            QStandardItem *row = new QStandardItem(QString(s));
            model->setItem(i,j,row);
            j++;
        }
        j = 0;
        i++;
    }
    fp.close();
}

void AcctMgr::on_pushButton_clicked()
{
    newTabIndex++;
    QString newAccount = ui->lineEdit->text();
    QTabWidget *myTabWidget = new QTabWidget(this);
    QTableView *myTableView = new QTableView(myTabWidget);
    ui->tabWidget->addTab(myTableView, newAccount);
    ui->tabWidget->setCurrentIndex(newTabIndex);


}
