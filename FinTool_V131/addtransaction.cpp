#include "addtransaction.h"
#include "ui_addtransaction.h"

addTransaction::addTransaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTransaction)
{
    ui->setupUi(this);
    this->Account = (QStringList() << (QString)"Default" << (QString) "Add Account");
    this->Categories = (QStringList() << (QString)"Default" << (QString)"Add Category");
    this->Transaction_types = (QStringList() << (QString)"Deposit" << (QString)"Withdrawl");
    ui->cb_account->addItems(this->Account);
    ui->cb_category->addItems(this->Categories);
    ui->cb_transaction->addItems(this->Transaction_types);

}

addTransaction::~addTransaction()
{
    delete ui;
}

//Getter functions to accessing widget data
QDate addTransaction::getDate(){
    return ui->dte_time_date->date();
}
QTime addTransaction::getTime(){
    return ui->dte_time_date->time();
}
double addTransaction::getAmount(){
    return ui->dsb_amount->value();
}
QString addTransaction::getAccount(){
    return ui->cb_account->currentText();
}
QString addTransaction::getInfo(){
    return ui->le_info->text();
}
QString addTransaction::getCategory(){
    return ui->cb_category->currentText();
}
QString addTransaction::getTransactionType(){
    return ui->cb_transaction->currentText();
}


//Functions to add types
void addTransaction::on_cb_account_currentIndexChanged(const QString &arg1)
{
    QString accountType = "";

    if(ui->cb_account->currentText() == "Add Account"){
        addType newAccType;
        if(newAccType.exec() == QDialog::Accepted){
            ui->cb_account->setCurrentIndex(0);
            accountType = newAccType.theString();
            this->Account += accountType;
            ui->cb_account->insertItem(ui->cb_account->findText("Add Account"), accountType);
        }
    }
}

void addTransaction::on_cb_category_currentIndexChanged(const QString &arg1)
{
    QString catType;
    if(ui->cb_category->currentText() == "Add Category"){
        addType newCatType;
        if(newCatType.exec() == QDialog::Accepted){
            ui->cb_category->setCurrentIndex(0);
            catType = newCatType.theString();
            this->Account += catType;
            ui->cb_category->insertItem(ui->cb_account->findText("Add Category"), catType);
        }
    }

}

void addTransaction::on_cb_transaction_currentIndexChanged(const QString &arg1)
{
    QString transType;
    if(ui->cb_transaction->currentText() == "Add Transaction Type"){
        addType newTransType;
        if(newTransType.exec() == QDialog::Accepted){
            ui->cb_transaction->setCurrentIndex(0);
            transType = newTransType.theString();
            this->Account += transType;
            ui->cb_transaction->insertItem(ui->cb_account->findText("Add Transaction Type"), transType);
        }
    }
}
