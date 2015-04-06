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

#include "createfirsttabaccount.h"
#include "addtabaccount.h"
#include "addtransaction.h"

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

    //END Setter Function

    bool FinTool::eventFilter(QObject *target, QEvent *event);

    //Function to import Tab Accounts by a username
    void importTabAccount(QString username);

    //fuction to import Tables from a username
    void importTables(QString username);


    QTableWidget* createTable(){
        QTableWidget *newTable = new QTableWidget();
        connect(newTable,SIGNAL(cellChanged(int,int)),this,SLOT(on_cell_item_changed(int, int)));
        connect(newTable,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(on_cell_item_doubleclicked(int,int)));
        return newTable;
    }

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

    void editTransactionFileTransactionType(QString edit, int totalRow, int row, int column);
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

        curTable->insertRow(0);
        curTable->setItem(0,0, new QTableWidgetItem(this->newTransactionData.Date.toString("dd/MM/yyyy")));
        curTable->setItem(0,1, new QTableWidgetItem(this->newTransactionData.transType));
        curTable->setItem(0,2, new QTableWidgetItem(this->newTransactionData.Category));
        curTable->setItem(0,3, new QTableWidgetItem(this->newTransactionData.information));
        curTable->setItem(0,4, new QTableWidgetItem(QString::number(this->newTransactionData.Amount)));
       // curTable->setItem(0,5, new QTableWidgetItem(QString::number(this->newTransactionData.curBalance)));

        calcBalanceBottomTop(curTable);
    }

    //Function for writing a transaction
    void writeTransaction(inputData transaction, QString User);

    //Function to easily format a *table
    void formatTable(QTableWidget *newTable){
         newTable->setColumnCount(6);
         newTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Date"));
         newTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Transaction"));
         newTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Category"));
         newTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Additional Info"));
         newTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Amount"));
         newTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Balance"));
    }


    //Function to check if there are any accounts in the 'username's' directory
    bool accountsExist(QString username){
        QString workingDir = "users/"+username+"/";
        QDir dir(workingDir);
        QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);

        if(accountList.size() > 1){
            return true;
        }
        else
            return false;
    }

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

public slots:
    void on_cell_item_changed(int, int);
    void on_cell_item_doubleclicked(int, int);

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    QString Username;
    QString Password;
    QString AccountType;
    QStringList categories;
    int curComboRow;
    int curComboColumn;
    inputData newTransactionData;
    Ui::FinTool *ui;
};

#endif // FINTOOL_H
