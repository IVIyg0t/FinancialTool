#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Login");
}

Login::~Login()
{
    delete ui;
}


QString Login::getUsername(){
    return ui->username->text();
}

QString Login::getPassword(){
    return ui->username->text();
}



void Login::on_signin_clicked()
{
    if(checkUserAccount(ui->username->text(),ui->password->text())){
        this->accept();
    }
    else{
        QMessageBox loginFailed;
        loginFailed.setText("Login failed, please try again or create a new account");
        loginFailed.exec();
    }
}


void Login::on_createaccount_clicked()
{
    createAccount newAccount;
    if(newAccount.exec() == QDialog::Accepted){
        this->username = newAccount.getUsername();
        this->password = newAccount.getPassword();

        createDir("users/"+this->username);
        writeString("users/"+this->username+"/categories"," ,Work,Groceries,Electric Bill,Gas");
        writeString("users/"+this->username+"/userAccount", this->username+","+this->password);

        ui->username->setText(this->username);
        ui->password->setText(this->password);
    }
}
