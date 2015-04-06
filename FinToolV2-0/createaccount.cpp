#include "createaccount.h"
#include "ui_createaccount.h"

createAccount::createAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createAccount)
{
    ui->setupUi(this);
    setWindowTitle("Create Account");
}

createAccount::~createAccount()
{
    delete ui;
}

QString createAccount::getUsername(){
    return ui->username->text();
}

QString createAccount::getPassword(){
    return ui->password->text();
}

void createAccount::on_createaccount_clicked()
{
    this->accept();
}

void createAccount::on_cancel_clicked()
{
    this->reject();
}
