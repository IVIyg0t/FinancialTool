#include "createaccount.h"
#include "ui_createaccount.h"

createAccount::createAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createAccount)
{
    ui->setupUi(this);
}

createAccount::~createAccount()
{
    delete ui;
}

QString createAccount::getUsername(){
    return ui->lineEdit->text();
}

QString createAccount::getPassword(){
    return ui->lineEdit_2->text();
}

QString createAccount::getFirstTab(){
    return ui->lineEdit_3->text();
}
