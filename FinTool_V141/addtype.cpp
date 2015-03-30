#include "addtype.h"
#include "ui_addtype.h"

addType::addType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addType)
{
    ui->setupUi(this);
}

addType::~addType()
{
    delete ui;
}

QString addType::theTabName(){
    return ui->lineEdit->text();
}
QString addType::theUsername(){
    return ui->lineEdit_3->text();
}
QString addType::thePassword(){
    return ui->lineEdit_2->text();
}
