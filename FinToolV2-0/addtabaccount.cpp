#include "addtabaccount.h"
#include "ui_addtabaccount.h"

addTabAccount::addTabAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTabAccount)
{
    ui->setupUi(this);

    //popup_init
    string_not_found.addButton(QMessageBox::Ok);
    string_not_found.setWindowTitle((QString)"Error: No account string found");
    string_not_found.setText((QString)"Please fill in a name for the account.");
}

addTabAccount::~addTabAccount()
{
    delete ui;
}

QString addTabAccount::getAccountName(){
    return ui->lineEdit->text();
}

QString addTabAccount::getAccountType(){
    return ui->comboBox->currentText();
}

void addTabAccount::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == NULL)
        string_not_found.show();

    bool foo = true;
    foreach(QString N, this->tabNames){
        if(N == this->getAccountName()+ " - " + this->getAccountType()){
            QMessageBox ErrMsg;
            ErrMsg.setText("Tisk tisk.. The Account your trying to create already exists!");
            ErrMsg.exec();
            foo = false;
        }
    }
    this->setState(foo);

    if(this->isGood())
        this->accept();
}

void addTabAccount::on_pushButton_2_clicked()
{
    this->reject();
}
