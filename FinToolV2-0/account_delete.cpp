#include "account_delete.h"
#include "ui_account_delete.h"
#include "fintool.h"

account_delete::account_delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account_delete)
{
    ui->setupUi(this);
}

account_delete::~account_delete()
{
    delete ui;
}

void account_delete::on_pushButton_2_clicked()
{
    this->reject();
    this->close();
}

void account_delete::on_pushButton_clicked()
{
    this->accept();
    this->close();
}

QString account_delete::get_Account(void)
{
    return ui->lineEdit->text();
}
