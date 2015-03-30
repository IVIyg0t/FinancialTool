#include "fintool.h"
#include "ui_fintool.h"

FinTool::FinTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinTool)
{
    ui->setupUi(this);
    userDialog login;

    //Display Login Window
    if(login.exec() == QDialog::Accepted){
        this->userName = login.getUsername();
        this->tabName = login.getFirstTab();
    }
    if(this->tabName != "")
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),this->tabName);
    setupTable();
    createFile("users/"+this->userName+"/"+this->tabName);

    //Create tabs for user (returning user)
    createTabAccounts(this->userName);


}

FinTool::~FinTool()
{
    delete ui;
}

void FinTool::createTabAccounts(QString username) {
    QDir dir("users/"+username+"/");
    QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);
    int iter = 0;
    foreach(QString file, accountList){
        if(file != "userAccount"){
            iter++;
            if(iter == 1)
                ui->tabWidget->setTabText(0,file);
            else{
                //QWidget *newtab = new QWidget(ui->tabWidget);
                QTableWidget *newTable = new QTableWidget(ui->tableWidget);
                newTable->setColumnCount(7);
                newTable->setRowCount(1);
                //Set names of columns
                newTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Date"));
                newTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Time"));
                newTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Type"));
                newTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Category"));
                newTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Amount"));
                newTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Info"));
                newTable->setHorizontalHeaderItem(6, new QTableWidgetItem("Balance"));

                ui->tabWidget->addTab(newTable,file);

                // QWidget *newTable = new QWidget(ui->tableWidget);
                ui->tabWidget->setCurrentIndex(iter-1);

            }
        }
    }
}

void FinTool::setupTable(){
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
