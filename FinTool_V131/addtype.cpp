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

QString addType::theString(){
    return ui->lineEdit->text();
}
