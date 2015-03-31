#include "addtype.h"
#include "ui_addtype.h"

addType::addType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addType)
{
    ui->setupUi(this);

    this->Account = (QStringList() << (QString)"Checking" << (QString)"Savings" << (QString)"CD");
    ui->comboBox->addItems(this->Account);
}

addType::~addType()
{
    delete ui;
}

QString addType::getText(){
    return ui->lineEdit->text();
}

QString addType::getAccountType(){
    return ui->comboBox->currentText();
}
