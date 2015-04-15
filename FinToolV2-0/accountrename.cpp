#include "accountrename.h"
#include "ui_accountrename.h"
#include <QMessageBox>
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

void accountRename::on_pushButton_clicked()
{
    bool foo = true;
   foreach(QString N, this->tabNames){
       if(N == this->getName()){
           QMessageBox ErrMsg;
           ErrMsg.setText("Tisk tisk... This account name already exists...");
           ErrMsg.exec();
           foo = false;
       }
   }

   this->setState(foo);

   if(this->isGood()){
       this->accept();
   }
}


void accountRename::on_pushButton_2_clicked()
{
    this->reject();
}
