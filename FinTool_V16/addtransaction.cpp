#include "addtransaction.h"
#include "ui_addtransaction.h"

addTransaction::addTransaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTransaction)
{
    ui->setupUi(this);



  //  this->Account = (QStringList() << (QString)"" << (QString) "Add Account");
  //  this->Categories = (QStringList() <<(QString)"Groceries" << (QString)"Electric bill" << (QString)"gas" << (QString)"Add Category");
    this->Transaction_types = (QStringList() << (QString)"Credit" << (QString)"Debit");

    //Install the Enter/Return filter for CB Add Types
   // ui->cb_account->installEventFilter(this);
    ui->cb_category->installEventFilter(this);
   // ui->cb_transaction->installEventFilter(this);

   // ui->cb_account->addItems(this->Account);
    genCategoryOptions();
    this->Categories += "Add Category";
    ui->cb_category->addItems(this->Categories);
    ui->cb_transaction->addItems(this->Transaction_types);

}

addTransaction::~addTransaction()
{
    delete ui;
}

 QStringList addTransaction::genCategoryOptions(){
     this->Categories.clear();
     QFile file("users/categories");
     file.open(QIODevice::ReadOnly);
     QTextStream in(&file);

     while(!in.atEnd()){
         QString Line = in.readLine();
         QStringList cats;

         cats.append(Line.split(','));

         foreach(QString it, cats){
             this->Categories += it;
         }
     }
     return this->Categories;
     file.close();
 }


//Getter functions to accessing widget data
QDate addTransaction::getDate(){
    return ui->dte_time_date->date();
}
QTime addTransaction::getTime(){
    return ui->dte_time_date->time();
}
double addTransaction::getAmount(){
    return ui->dsb_amount->value();
}
//QString addTransaction::getAccount(){
//    return ui->cb_account->currentText();
//}
QString addTransaction::getInfo(){
    return ui->le_info->text();
}
QString addTransaction::getCategory(){
    return ui->cb_category->currentText();
}
QString addTransaction::getTransactionType(){
    return ui->cb_transaction->currentText();
}


//Functions to add types
//void addTransaction::on_cb_account_currentIndexChanged(const QString &arg1)
//{
//   if(arg1 == QString("Add Account")){
//      ui->cb_account->setEditable(true);
//      ui->cb_account->clearEditText();
//   }
//   else if(this->Account.contains(arg1, Qt::CaseInsensitive)){
//      ui->cb_account->setEditable(false);
//   }
//}

void addTransaction::on_cb_category_currentIndexChanged(const QString &arg1)
{
    if(arg1 == QString("Add Category")){
        ui->cb_category->setEditable(true);
        ui->cb_category->clearEditText();
    }
    else if(this->Categories.contains(arg1,Qt::CaseInsensitive)){
        ui->cb_category->setEditable(false);
    }
}

//void addTransaction::on_cb_transaction_currentIndexChanged(const QString &arg1)
//{
//    if(arg1 == QString("Add Transaction Type")){
//        ui->cb_transaction->setEditable(true);
//        ui->cb_transaction->clearEditText();
//    }
//    else if(this->Account.contains(arg1, Qt::CaseInsensitive)){
//        ui->cb_transaction->setEditable(false);
//    }
//}

bool addTransaction::eventFilter(QObject *target, QEvent *event){
    QString newType;
    if(target == ui->cb_category || target == ui->cb_transaction){
        if(event->type() == QEvent::KeyPress){
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
                if((keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return)){
//                    if(target == ui->cb_account){
//                        newType =  ui->cb_account->currentText();
//                        this->Account += newType;
//                        ui->cb_account->insertItem(ui->cb_account->findText("Add Account"), newType);
//                        ui->cb_account->setCurrentIndex(ui->cb_account->findText(newType));
//                        ui->cb_category->setFocus();
//                        return true;
//                    }

                    if(target == ui->cb_category){
                        QFile file("users/categories");
                        file.open(QIODevice::WriteOnly | QIODevice::Append);
                        QTextStream out(&file);
                        QString curText = ui->cb_category->currentText();
                        out << ","+curText;
                        //this->Categories += newType;
                        file.close();
                        genCategoryOptions();

                        ui->cb_category->insertItem(ui->cb_category->findText("Add Category"), curText);
                        ui->cb_category->setCurrentIndex(ui->cb_category->findText(curText));
                        ui->cb_transaction->setFocus();
                        return true;
                    }

//                    if(target == ui->cb_transaction){
//                        newType = ui->cb_transaction->currentText();
//                        this->Transaction_types += newType;
//                        ui->cb_transaction->insertItem(ui->cb_transaction->findText("Add Transaction Type"), newType);
//                        ui->cb_transaction->setCurrentIndex(ui->cb_transaction->findText(newType));
//                        ui->le_info->setFocus();
//                        return true;
//                    }
                }
            }
        }
        return QDialog::eventFilter(target,event);
    }

void addTransaction::on_pushButton_clicked()
{
    QStringList Missing_Fields;

    if(ui->dsb_amount->value() == 0.0)
        Missing_Fields << "Amount";
    if(ui->cb_category->currentText() == NULL)
        Missing_Fields << "Category";
    if(ui->cb_transaction->currentText() == NULL)
        Missing_Fields << "Transaction Type";

    if(Missing_Fields.length() == 0){
        this->accept();
//        ui->cb_category->setCurrentIndex(0);
//        ui->cb_transaction->setCurrentIndex(0);
    }
    else{
        Required_fields.setText("Please enter the following fields: "+Missing_Fields.join(',')+".");
        Required_fields.show();
    }
}

void addTransaction::on_pushButton_2_clicked()
{
    this->reject();
}
