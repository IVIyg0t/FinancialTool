#include "fintool.h"
#include "ui_fintool.h"


FinTool::FinTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinTool)
{
    ui->setupUi(this);

    connect(ui->add_transaction,SIGNAL(triggered()),this,SLOT(on_actionadd_transaction_triggered()));

    //Name the first tab
    //ui->tabWidget->setTabText(0,"cash");




    //Create users directory if it doesn't exist
    if(!userDirExists())
       createUsersDir();

    //Check if the Users Directory is empty
    //Might implement this portion as a function later.
    QString firstTab = "";
    QString userName = "";
    QString Password = "";
    if(QDir("users").entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0){
       addType addTab;
       if(addTab.exec() == QDialog::Accepted){  //Query User to create the first account if users directory is empty
           firstTab = addTab.theTabName();
           userName = addTab.theUsername();
           Password = addTab.thePassword();
           createDir(userName);
           ui->tabWidget->setTabText(0, firstTab);
           QString path = "users/"+userName+"/"+firstTab;
           fileCreate(path);    //Create a file with the name of the account users/userName/firstTab
           fileCreate("users/"+userName+"/"+"userAccount"); //create a user account file to keep record of username/password
           writeString("users/"+userName+"/"+"userAccount", userName+","+Password);
       }

    }
    else{
       QDir dir("users");
       QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);
       foreach (QString file,accountList) {
           QWidget *newTab = new QWidget(ui->tabWidget);
           ui->tabWidget->addTab(newTab,file);
       }
    }
    //create some columns and rows
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(1);
    //Set names of columns
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Date"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Time"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Type"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Category"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Amount"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Info"));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Balance"));
}

FinTool::~FinTool()
{
    delete ui;
}

bool FinTool::fileExists(QString path){
    QFileInfo checkFile(path);
    //Check if file exists and if yes: is it really a file and not a directory?
    if(checkFile.exists() && checkFile.isFile()){
        return true;
    } else {
        return false;
    }
}

bool FinTool::userDirExists(){
    QDir users("users");
    if(!users.exists()){
        return false;
    }
    else
        return true;
}
void FinTool::writeString(QString fileName, QString info){
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << info;
    file.close();
}

void FinTool::createDir(QString name){
    QDir().mkdir("users/"+name);
}

void FinTool::createUsersDir(){
    QDir().mkdir("users");
}

void FinTool::fileCreate(QString name){
    QFile file(name);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void FinTool::writeTransaction(inputData transaction){
    QFile file("users/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);
    out << transaction.Date.toString("dd:MM:yyyy") << ",";
    out << transaction.Time.toString("h:mm AP") << ",";
    if(transaction.Account != "")
        out << transaction.Account << ",";
    else
        out << "N/A" << ",";
    if(transaction.Category != "")
        out << transaction.Category << ",";
    else
        out << "N/A" << ",";
    if(transaction.transType != "")
        out << transaction.transType << ",";
    else
        out << "N/A" << ",";

    out << transaction.Amount << ",";

    if(transaction.Information != "")
        out << transaction.Information << "\n";
    else
        out << "N/A" << "\n";
    file.close();

}

void FinTool::on_actionadd_transaction_triggered(){
    addTransaction dialog;
    inputData transaction;
    if(dialog.exec() == QDialog::Accepted){
        transaction.Account = dialog.getAccount();
        transaction.Amount = dialog.getAmount();
        transaction.Category = dialog.getCategory();
        transaction.Date = dialog.getDate();
        transaction.Time = dialog.getTime();
        transaction.Information = dialog.getInfo();
        transaction.transType = dialog.getTransactionType();
        transaction.success = true;
    }


    if(transaction.success == true){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(transaction.Date.toString("dd:MM:yyyy")));
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(transaction.Time.toString("h:mm AP")));
        ui->tableWidget->setItem(0,2, new QTableWidgetItem(transaction.transType));
        ui->tableWidget->setItem(0,3, new QTableWidgetItem(transaction.Category));
        ui->tableWidget->setItem(0,4, new QTableWidgetItem(QString::number(transaction.Amount)));
        ui->tableWidget->setItem(0,5, new QTableWidgetItem(transaction.Information));
        writeTransaction(transaction);

    }


}
