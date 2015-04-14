#ifndef FINTOOL_H
#define FINTOOL_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QTime>
#include <QDate>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QDebug>
#include <QComboBox>
#include <QDialog>
#include <QFont>
#include <QMenu>
#include <QHeaderView>
#include <QCalendarWidget>

#include "graph.h"
#include "createfirsttabaccount.h"
#include "addtabaccount.h"
#include "addtransaction.h"
#include "account_delete.h"

struct inputData{
    QString information;
    QString Account;
    QString Category;
    QString transType;
    QDate Date;
    double Amount;
    double curBalance;
    double prevBalance;
    bool success;
};

namespace Ui {
class FinTool;
}

class FinTool : public QMainWindow
{
    Q_OBJECT

public slots:
    void on_action_add_bank_account_triggered();
    void on_action_add_transaction_triggered();
    void on_actionAccount_Deletion_triggered();

public:
    explicit FinTool(QString username, QWidget *parent = 0);
    ~FinTool();

    //Setter Functions

    void setUsername(QString username){
        Username = username;
    }

    void setPassword(QString password){
        Password = password;
    }


    bool FinTool::eventFilter(QObject *target, QEvent *event);


  //////////////////////////* Functions for generating reports *//////////////////////////

    //Function to generate balance report
    void genBalanceReport();

    // Function to generate income report
    void genIncomeReport();

    // Function to generate Expense report
    void genSpendingAnalysisReport();


/////////////////////////////* Existing User Functions *//////////////////////////////////


    //Function to import Tab Accounts by a username
    void importTabAccount(QString username);

    //fuction to import Tables from a username
    void importTables(QString username);


//////////////////////////////* Bool Functions *//////////////////////////////////////////

    //Function to check if there are any accounts in the 'username's' directory
    bool accountsExist(QString username){
        QString workingDir = "users/"+username+"/";
        QDir dir(workingDir);
        QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);

        if(accountList.size() > 2){
            return true;
        }
        else
            return false;
    }

    // Function to delete a file, takes the path of the file as an argument
    void delFile(QString path){
        QFile::remove(path);
    }

    //Function to check if a file exists
    bool fileExists(QString path){
        QFileInfo checkFile(path);

        if(checkFile.exists() && checkFile.isFile()){
            return true;
        }else
            return false;
    }

    //Function to check if a directory exists
    bool dirExists(QString path){
        QDir dir(path);
        if(dir.exists())
            return true;
        else
            return false;
    }

    // Function to authenticate a user account when they login
    bool checkUserAccount(QString username, QString password){
        QFile file("users/"+username+"/userAccount");
        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QStringList creds;

        creds.append(line.split(','));

        //Validate user creds
        if(username == creds.at(0) && password == creds.at(1))
            return true;
        else
            return false;
    }



//////////////////////////////* Funtions for File I/O Operations *//////////////////////////////

    // Rewrite transactions to file
    void rewriteTableToFile(QTableWidget *curTable);


    // Function to generate the list of category type options from the categories file
    QStringList genCategoryOptions(){
        this->categories.clear();
        QFile file("users/"+this->Username+"/categories");
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList cats;
            cats.append(line.split(','));

            foreach(QString s, cats){
                this->categories += s;
            }
        }
        return this->categories;
        file.close();
    }

    //Function to update the account files when user edits a transaction in the table
    void editTransactionFileAmount(QString edit,int totalRow, int row, int column);

    // Function to write a transaction to a file
    void writeTransaction(inputData transaction, QString User);

    //Function to create a directory
    void createDir(QString path){
        QDir().mkdir(path);
    }

    //Function to create a file
    void createFile(QString path){
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    //Function to write & append a string to a file
    void writeString(QString fileName, QString data){
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream out(&file);
        out << data;
        file.close();
    }



/////////////////////////////////* Functions that Edit the QTableWidgets */////////////////////////


    // Function to sort entries in the table



    // Function to create a QTableWidget
    QTableWidget* createTable(){
        QTableWidget *newTable = new QTableWidget();
        newTable->setContextMenuPolicy(Qt::CustomContextMenu);
        //newTable->horizontalHeader()->setSortIndicatorShown(true);
         //newTable->setSortingEnabled(true);
        newTable->setSortingEnabled(true);
        //newTable->sortByColumn(0, Qt::DescendingOrder);
        connect(newTable,SIGNAL(cellChanged(int,int)),this,SLOT(on_cell_item_changed(int, int)));
        connect(newTable,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(on_cell_item_doubleclicked(int,int)));
        connect(newTable,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(cellMenu(const QPoint &)));
        return newTable;
    }


    //Calculate current balance
    void convertAmount(){
        if(this->newTransactionData.transType == "Expense"){
            this->newTransactionData.Amount = (this->newTransactionData.Amount*-1);
        }
    }

    // Calculate Balance from bottom to top of table
    void calcBalanceBottomTop(QTableWidget *curTable){
        int rowCount = curTable->rowCount();
        this->newTransactionData.curBalance = 0;
        for(int i = rowCount-1; i >= 0; i--){
            QTableWidgetItem *curItem = curTable->item(i,4);
            double theValue = curItem->text().toDouble();
            qDebug() << theValue << "\n" << i;
            this->newTransactionData.curBalance += theValue;

            curTable->setItem(i,5, new QTableWidgetItem(QString::number(this->newTransactionData.curBalance)));
        }
    }


    //Function for setting a transaction to the curTable
    void setTransactionToCurrentTable(QTableWidget *curTable){
        if(curTable->rowCount() == 0) {
            curTable->insertRow(0);
            curTable->setItem(0,0, new QTableWidgetItem(this->newTransactionData.Date.toString("M/d/yyyy")));
            curTable->setItem(0,1, new QTableWidgetItem(this->newTransactionData.transType));
            curTable->setItem(0,2, new QTableWidgetItem(this->newTransactionData.Category));
            curTable->setItem(0,3, new QTableWidgetItem(this->newTransactionData.information));
            curTable->setItem(0,4, new QTableWidgetItem(QString::number(this->newTransactionData.Amount)));

            // curTable->setItem(0,5, new QTableWidgetItem(QString::number(this->newTransactionData.curBalance)));
        }
        else{
            int i = 0;
            //curTable->blockSignals(true);
            while(i < curTable->rowCount()){
                QDate tDate = QDate::fromString(curTable->item(i,0)->text(),"M/d/yyyy");
                if(this->newTransactionData.Date >= tDate){
                    curTable->insertRow(i);
                    curTable->setItem(i,0, new QTableWidgetItem(this->newTransactionData.Date.toString("M/d/yyyy")));
                    curTable->setItem(i,1, new QTableWidgetItem(this->newTransactionData.transType));
                    curTable->setItem(i,2, new QTableWidgetItem(this->newTransactionData.Category));
                    curTable->setItem(i,3, new QTableWidgetItem(this->newTransactionData.information));
                    curTable->setItem(i,4, new QTableWidgetItem(QString::number(this->newTransactionData.Amount)));
                    break;
                }
                else if(i == curTable->rowCount()-1){
                    curTable->insertRow(i+1);
                    curTable->setItem(i+1,0, new QTableWidgetItem(this->newTransactionData.Date.toString("M/d/yyyy")));
                    curTable->setItem(i+1,1, new QTableWidgetItem(this->newTransactionData.transType));
                    curTable->setItem(i+1,2, new QTableWidgetItem(this->newTransactionData.Category));
                    curTable->setItem(i+1,3, new QTableWidgetItem(this->newTransactionData.information));
                    curTable->setItem(i+1,4, new QTableWidgetItem(QString::number(this->newTransactionData.Amount)));
                    break;

                }
                i++;
            }
            //curTable->blockSignals(false);
        }

        calcBalanceBottomTop(curTable);
    }

    //Function for writing a transaction

    //Function to easily format a *table
    void formatTable(QTableWidget *newTable){
         newTable->setColumnCount(6);
         newTable->horizontalHeader()->setStretchLastSection(true);
         newTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Date"));
         newTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Transaction"));
         newTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Category"));
         newTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Info"));
         newTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Amount"));
         newTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Balance"));
    }



public slots:
    void on_cell_date_changed();
    void on_cell_item_changed(int, int);
    void on_cell_item_doubleclicked(int, int);
    void cellMenu(const QPoint &);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_reports_addbankaccount_clicked();
    void on_date_changed();


private:
    QString Username;
    QString Password;
    QString AccountType;
    QStringList categories;
    int curComboRow;
    int curComboColumn;
    inputData newTransactionData;
    Ui::FinTool *ui;
    QMessageBox check;
};

#endif // FINTOOL_H
