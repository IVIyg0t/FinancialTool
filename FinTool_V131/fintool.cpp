#include "fintool.h"
#include "ui_fintool.h"


FinTool::FinTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinTool)
{
    ui->setupUi(this);

    connect(ui->add_transaction,SIGNAL(triggered()),this,SLOT(on_actionadd_transaction_triggered()));

       //Name the first tab
       ui->tabWidget->setTabText(0,"cash");

       //create some columns and rows
       ui->tableWidget->setColumnCount(7);
       ui->tableWidget->setRowCount(1);

       //Set names of columns
       ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Date"));
       ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Time"));
       ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Type"));
       ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Category"));
       ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Amount"));
       ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Info"));
       ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Balance"));


}

FinTool::~FinTool()
{
    delete ui;
}

void FinTool::on_actionadd_transaction_triggered(){
    addTransaction dialog;
    inputData transaction;
    if(dialog.exec() == QDialog::Accepted){
        transaction.Account = dialog.getAccount();
        transaction.Amount = dialog.getAmount();
        transaction.Category = dialog.getCategory();
        transaction.Date = dialog.getDate();
        transaction.Time = dialog.getTime();
        transaction.Information = dialog.getInfo();
        transaction.transType = dialog.getTransactionType();
        transaction.success = true;
    }


    if(transaction.success == true){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(transaction.Date.toString("dd:MM:yyyy")));
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(transaction.Time.toString("h:mm AP")));
        ui->tableWidget->setItem(0,2, new QTableWidgetItem(transaction.transType));
        ui->tableWidget->setItem(0,3, new QTableWidgetItem(transaction.Category));
        ui->tableWidget->setItem(0,4, new QTableWidgetItem(QString::number(transaction.Amount)));
        ui->tableWidget->setItem(0,5, new QTableWidgetItem(transaction.Information));

    }


}
