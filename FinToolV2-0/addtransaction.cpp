#include "addtransaction.h"
#include "ui_addtransaction.h"

addTransaction::addTransaction(QString Username,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTransaction)
{
    ui->setupUi(this);
    ui->Category->installEventFilter(this);
    this->username = Username;
    genCategoryOptions();
    this->categories += "Add Category";
    this->transtypes = (QStringList() << (QString)"Credit" << (QString)"Debit");
    ui->Category->addItems(this->categories);
    ui->TransactionType->addItems(this->transtypes);
}

addTransaction::~addTransaction()
{
    delete ui;
}

QStringList addTransaction::genCategoryOptions(){
    //this->categories.clear();
    QFile file("users/"+this->username+"/categories");
    qDebug() << this->username;
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList cats;
         cats.append(line.split(','));

         foreach(QString it, cats){
             this->categories += it;
         }
    }
    return this->categories;
    file.close();
}

QDate addTransaction::getDate(){
    return ui->date->date();
}

QString addTransaction::getCategory(){
    return ui->Category->currentText();
}

QString addTransaction::getTransactionType(){
    return ui->TransactionType->currentText();
}

QString addTransaction::getAddInfo(){
    return ui->addInfo->text();
}

double addTransaction::getAmount(){
    return ui->Amount->value();
}

bool addTransaction::eventFilter(QObject *target, QEvent *event){
    QString newType;
    if(target == ui->Category){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if((keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return)){
                QFile file("users/"+this->username+"/categories");
                file.open(QIODevice::WriteOnly | QIODevice::Append);
                QTextStream out(&file);

                QString curText = ui->Category->currentText();
                out <<","+curText;

                file.close();
                genCategoryOptions();

                ui->Category->insertItem(ui->Category->findText("Add Category"), curText);
                ui->Category->setCurrentIndex(ui->Category->findText(curText));
                return true;
            }
        }
    }
    return QDialog::eventFilter(target,event);
}

void addTransaction::on_Category_currentIndexChanged(const QString &arg1)
{
    if(arg1 == QString("Add Category")){
        ui->Category->setEditable(true);
        ui->Category->clearEditText();
    }
    else if(this->categories.contains(arg1,Qt::CaseInsensitive)){
        ui->Category->setEditable(false);
    }

}
