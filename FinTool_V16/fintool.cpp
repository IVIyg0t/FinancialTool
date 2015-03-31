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
    connect(ui->actionAccount, SIGNAL(triggered()), this, SLOT(on_action_account_triggered()));


    //Display Login Window
    if(login.exec() == QDialog::Accepted){
        this->userName = login.getUsername();
        this->tabName = login.getFirstTab();
        this->AccountType = login.getAccountType();

    }
    if(this->tabName != ""){
        //ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),this->tabName);
        createFile("users/"+this->userName+"/"+this->tabName+" - "+this->AccountType);
        createFile("users/categories");
        writeString("users/categories", "Groceries,Electric bill,gas");
    }
    setupTable();

    //Create file to store categories
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
                   // QWidget *page = ui->tabWidget->widget(tabIndex);  // Create a pointer to the widget inside the current tab
                   // QTableWidget *table = page->findChild<QTableWidget *>(); // create a QTableWidget pointer to the QTableWidget inside the page
                   QTableWidget *table = ui->tabWidget->widget(tabIndex)->findChild<QTableWidget *>();
                   if(j == 0)   // If j == 0 then we need to insert a new row at the top for importing our transaction into
                        table->insertRow(0);
                    table->setItem(0,j, new QTableWidgetItem(s)); // Set the current item ("s") into the 0th row and the jth column
                    j++;
                }
                j = 0;
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
                newTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Category"));
                newTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Info"));
                newTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Transaction"));
                newTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Amount"));
                newTable->setHorizontalHeaderItem(6, new QTableWidgetItem("Balance"));

                newTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

                ui->tabWidget->addTab(new QWidget(),file);
                QWidget *wgt = ui->tabWidget->widget(iter-1);
                QGridLayout *grid = new QGridLayout;
                grid->addWidget(newTable);
                wgt->setLayout(grid);


                //ui->tabWidget->addTab(wgt,file);

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
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Category"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Info"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Transaction"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Amount"));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Balance"));
}

void FinTool::on_action_transaction_triggered(){
    addTransaction dialog;
    inputData transaction;
    if(dialog.exec() == QDialog::Accepted){
      //  transaction.Account = dialog.getAccount();
        transaction.Amount = dialog.getAmount();
        transaction.Category = dialog.getCategory();
        transaction.Date = dialog.getDate();
        transaction.Time = dialog.getTime();
        transaction.Information = dialog.getInfo();
        transaction.transType = dialog.getTransactionType();
        transaction.success = true;
    }

    if(transaction.success == true){

        QTableWidget *currentTable = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QTableWidget *>();

        currentTable->insertRow(0);
        currentTable->setItem(0,0, new QTableWidgetItem(transaction.Date.toString("dd:MM:yyyy")));
        currentTable->setItem(0,1, new QTableWidgetItem(transaction.Time.toString("h:mm AP")));
        currentTable->setItem(0,2, new QTableWidgetItem(transaction.Category));
        currentTable->setItem(0,3, new QTableWidgetItem(transaction.Information));
        currentTable->setItem(0,4, new QTableWidgetItem(transaction.transType));
        currentTable->setItem(0,5, new QTableWidgetItem(QString::number(transaction.Amount)));
        writeTransaction(transaction, this->userName);

    }
}

void FinTool::on_action_account_triggered(){
    addType dialog;
    if(dialog.exec() == QDialog::Accepted){
        //Create a tab in the QTab widget and add a QTableWidget inside
        QTableWidget *newTable = new QTableWidget(ui->tableWidget);

        // Format the newTable
        newTable->setColumnCount(7);
        newTable->setRowCount(1);

        newTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Date"));
        newTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Time"));
        newTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Category"));
        newTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Info"));
        newTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Transaction"));
        newTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Amount"));
        newTable->setHorizontalHeaderItem(6, new QTableWidgetItem("Balance"));

        // Create a new QWidget and place it in a new tab in the QTabWidget
        ui->tabWidget->addTab(new QWidget(), dialog.getText()+" - "+dialog.getAccountType());

        // Create a QWidget and set it equal to the QWidget we just placed in the new tab
        QWidget *wgt = ui->tabWidget->widget(ui->tabWidget->count()-1);

        // Create a new QGridLayout
        QGridLayout *grid = new QGridLayout;

        // Add the table to the grid layout
        grid->addWidget(newTable);

        // Add the whole layout container into the tab's widget container
        wgt->setLayout(grid);


        // Now we need to create the file for writing to
        // using the createFile method referenced in
        // fintool.h
        QString path = "users/" + this->userName + "/" + dialog.getText() + " - " + dialog.getAccountType();
        createFile(path);

    }
}

void FinTool::writeTransaction(inputData transaction, QString username){
    QFile file("users/"+username+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream out(&file);

    out << transaction.Date.toString("dd:MM:yyyy") << ",";
    out << transaction.Time.toString("h:mm AP") << ",";

    if(transaction.Category != "")
        out << transaction.Category << ",";
    else
        out << "N/A,";

    if(transaction.Information != "")
        out << transaction.Information << ",";
    else
        out << "N/A\n";

    if(transaction.transType != "")
        out << transaction.transType << ",";
    else
        out << "N/A,";

    out << transaction.Amount << "\n";


    file.close();
}
