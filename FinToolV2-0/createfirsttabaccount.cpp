#include "createfirsttabaccount.h"
#include "ui_createfirsttabaccount.h"

createFirstTabAccount::createFirstTabAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createFirstTabAccount)
{
    ui->setupUi(this);
}

createFirstTabAccount::~createFirstTabAccount()
{
    delete ui;
}

QString createFirstTabAccount::getAccountName(){
    return ui->lineEdit->text();
}

QString createFirstTabAccount::getAccountType(){
    return ui->comboBox->currentText();
}
