#include "fintool.h"
#include "ui_fintool.h"

static int balance = 0;

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

        //added
        QString buffer = QString::number(balance);
        ui->tableWidget->setItem(0,6, new QTableWidgetItem((QString)buffer));

    }


}


//some terrible code that calculates balance which is a global cuz this code sucks
void FinTool::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    static int case_add_sub = -1;
    QVariant q = item->data(0);
    QStringList list = q.toStringList();
    QString check;
    qDebug() << list;


    //could run into an error where the user inputs "Deposit" or "Withdrawl" as their comment to the entry but it actually being the opposite for the next entry.
    foreach(check, list)
    {
        if(check == "Deposit")
            case_add_sub = 0;
        else if(check == "Withdrawl")
            case_add_sub = 1;
    }

    switch(case_add_sub)
    {
        case 0:
            if(q.toInt()!=balance)
                balance += q.toInt(0);
            break;
        case 1:
            if(q.toInt()!=balance)
                balance -= q.toInt(0);
            break;
        //Problem is this signal is being called every single time the table is changed.
        //This means its called like six times from one entry addition.
        //This means that the addition or subtraction needs to be set before recieving the number to add
        //If deposit or withdrawn isn't entered this default statement will only catch it on the first run through because case_add_sub is static
        default:
            qDebug() << "Error: Deposit or Withdrawl were not selected as transaction type.";
    }

    qDebug() << balance;
}
