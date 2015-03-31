#ifndef FINTOOL_H
#define FINTOOL_H

#include <QMainWindow>
#include "userdialog.h"
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTime>
#include <QString>
#include <QDate>
#include <QStringList>
#include <QTableWidget>
#include "addtransaction.h"

struct inputData {
    QString Information;
    double Amount;
    QTime Time;
    QDate Date;
    QString Account;
    QString Category;
    QString transType;
    bool success;
};

namespace Ui {
class FinTool;
}

class FinTool : public QMainWindow
{
    Q_OBJECT

public:
    QString userName;
    QString tabName;
    QString AccountType;

    explicit FinTool(QWidget *parent = 0);
    ~FinTool();

    bool fileExists(QString path){
        QFileInfo checkFile(path);
        //Check if file exists and if yes; is it really a file and not a directory?
        if(checkFile.exists() && checkFile.isFile()){
            return true;
        }else
            return false;
    }

    bool dirExists(QString path){
        QDir dir(path);
        if(dir.exists())
            return true;
        else
            return false;
    }

    void createDir(QString path){
        QDir().mkdir(path);
    }

    void createFile(QString path){
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    void writeString(QString fileName, QString info){
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream out(&file);
        out << info;
        file.close();
    }

    void writeTransaction(inputData transaction, QString username);

    bool checkUserAccount(QString username, QString password){
        QFile file("users/"+username+"/userAccount");
        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QStringList creds;

        creds.append(line.split(','));

        //Check user credentials.
        if(username == creds.at(0) && password == creds.at(1))
            return true;
        else
            return false;
    }

    void setupTable();

    void createTabAccounts(QString username);

    void populateTables(QString username);

public slots:
    void on_action_transaction_triggered();
    void on_action_account_triggered();

private:
    Ui::FinTool *ui;
};

#endif // FINTOOL_H
