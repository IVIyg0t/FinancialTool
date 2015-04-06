#include "addtabaccount.h"
#include "ui_addtabaccount.h"

addTabAccount::addTabAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTabAccount)
{
    ui->setupUi(this);
}

addTabAccount::~addTabAccount()
{
    delete ui;
}

QString addTabAccount::getAccountName(){
    return ui->lineEdit->text();
}

QString addTabAccount::getAccountType(){
    return ui->comboBox->currentText();
}
