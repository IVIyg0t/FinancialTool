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
       if(N == this->getName())
       {
           QMessageBox ErrMsg;
           ErrMsg.setText("The account your trying to create already exists!");
           ErrMsg.exec();
           foo = false;
       }
       //Makes any case varaiation of the word "reports" protected and unuseable for an account tab.
       if(this->getName().contains("Reports",Qt::CaseInsensitive))
       {
           QMessageBox ErrMsg;
           ErrMsg.setText("Reports is a protected name and cannot be used for an account name!");
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
