#include "userdialog.h"
#include "ui_userdialog.h"

userDialog::userDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userDialog)
{
    ui->setupUi(this);
}

userDialog::~userDialog()
{
    delete ui;
}

QString userDialog::getUsername(){
    return ui->lineEdit->text();
}

QString userDialog::getPassword(){
    return ui->lineEdit_2->text();
}

void userDialog::on_createaccount_clicked()
{
    createAccount newAccount;
    if(newAccount.exec() == QDialog::Accepted){
        this->username = newAccount.getUsername();
        this->password = newAccount.getPassword();
        this->FirstTab = newAccount.getFirstTab();
        this->accountType = newAccount.getAccountType();

        createDir("users/"+this->username);
        writeString("users/"+this->username+"/userAccount",this->username+","+this->password);

        ui->lineEdit->setText(this->username);
        ui->lineEdit_2->setText(this->password);
    }
}

void userDialog::on_signin_clicked()
{
    if(checkUserAccount(ui->lineEdit->text(),ui->lineEdit_2->text())){
        this->accept();
    }
    else{
        QMessageBox loginFailed;
        loginFailed.setText("Login failed, please try again or create a new account");
        loginFailed.exec();
    }
}
