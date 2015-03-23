#include "addnewtransaction.h"
#include "ui_addnewtransaction.h"

addNewTransaction::addNewTransaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewTransaction)
{
    ui->setupUi(this);
}

addNewTransaction::~addNewTransaction()
{
    delete ui;
}

void addNewTransaction::on_buttonBox_accepted()
{

}

QStringList grabTransData(){
    QStringList transValues;

    //transValues.append(ui->lineEdit->text());
   // transValues.append(ui->lineEdit_2->text());
   // transvalues.append(ui->lineEdit_3->text());
   // transValues.append(ui->lineEdit_4->text());
   // transvalues.append(ui->lineEdit_5->text());

    return transValues;
}
