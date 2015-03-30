#include "fintool.h"
#include "ui_fintool.h"
#include <QDebug>

FinTool::FinTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinTool)
{
    ui->setupUi(this);
    userDialog login;

    //Connect Add Transaction menu item to transaction dialog
    connect(ui->actionTransaction,SIGNAL(triggered()), this, SLOT(on_action_transaction_triggered()));

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
    populateTables(this->userName);


}

FinTool::~FinTool()
{
    delete ui;
}

//Function to populate tables after tabs have been populated
void FinTool::populateTables(QString username){
    // Directory variables
    QString workingDir = "users/"+username+"/";
    QDir dir(workingDir);
    QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);

    // For each item in accountList as "file" do the following
    // loop will iterate through each file in the current users directory
    foreach(QString file, accountList){

        // Exclude the "userAccount" file from the operations
        if(file != "userAccount"){
            qDebug(file.toLatin1());

            // Variables for reading from file
            QFile fp(workingDir+file);
            fp.open(QIODevice::ReadOnly);
            QTextStream in(&fp);

            // Read the current 'file' until we reach the end
            while(!in.atEnd()){

                // Read in the current line
                QString Line = in.readLine();
                QStringList transDeets;
                int tabIndex = -1;

                // Split the current line by ',' and place each element into a string list
                transDeets.append(Line.split(','));

                // Find the tab that matches the current file we're working on.
                // I.E: if file is "BoA Checking" then the tab name is "BoA Checking"
                for(int k = 0; k < ui->tabWidget->count(); k++){
                    if(file == ui->tabWidget->tabText(k)){
                        tabIndex = k;
                        break;
                    }
                }

                // For each element in transDeets (Transaction Details) as "s" do the following
                int j = 0;
                foreach(QString s, transDeets){
                    qDebug(s.toLatin1());
                    QWidget *page = ui->tabWidget->widget(tabIndex);  // Create a pointer to the widget inside the current tab
                    QTableWidget *table = page->findChild<QTableWidget *>(); // create a QTableWidget pointer to the QTableWidget inside the page
                    if(j == 0)   // If j == 0 then we need to insert a new row at the top for importing our transaction into
                        table->insertRow(0);
                    table->setItem(0,j, new QTableWidgetItem(s)); // Set the current item ("s") into the 0th row and the jth column
                    j++;
                }
            }
            fp.close(); //Outside of while() , Close the file.
        }
    }
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

void FinTool::on_action_transaction_triggered(){
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
        writeTransaction(transaction, this->userName);
    }
}

void FinTool::writeTransaction(inputData transaction, QString username){
    QFile file("users/"+username+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream out(&file);

    out << transaction.Date.toString("dd:MM:yyyy") << ",";
    out << transaction.Time.toString("h:mm AP") << ",";
    if(transaction.Account != "")
        out << transaction.Account << ",";
    else
        out << "N/A,";
    if(transaction.transType != "")
        out << transaction.transType << ",";
    else
        out << "N/A,";

    out << transaction.Amount << ",";

    if(transaction.Information != "")
        out << transaction.Information << "\n";
    else
        out << "N/A\n";
    file.close();
}
