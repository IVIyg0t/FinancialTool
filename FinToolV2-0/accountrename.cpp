#include "accountrename.h"
#include "ui_accountrename.h"

accountRename::accountRename(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountRename)
{
    ui->setupUi(this);
}

accountRename::~accountRename()
{
    delete ui;
}

QString accountRename::getName(){
    return ui->lineEdit->text();
}
