#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "createaccount.h"
#include <QFile>
#include <QString>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
namespace Ui {
class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    QString username;
    QString password;
    QString FirstTab;
    QString accountType;

    explicit userDialog(QWidget *parent = 0);
    ~userDialog();

    QString getUsername();
    QString getPassword();
    QString getNewUsername(){
        return username;
    }

    QString getNewPassword(){
        return password;
    }

    QString getFirstTab(){
        return FirstTab;
    }

    QString getAccountType(){
        return accountType;
    }

    void createDir(QString path){
        QDir().mkpath(path);
    }
    void writeString(QString fileName, QString info){
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << info;
        file.close();
    }

    bool checkUserAccount(QString username, QString password){
        QFile file("users/"+username+"/userAccount");
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString line = in.readLine();
        QStringList creds;
        creds.append(line.split(','));

        //Check user creds
        if(username == creds.at(0) && password == creds.at(1))
            return true;
        else
            return false;
    }

private slots:
    void on_signin_clicked();

    void on_createaccount_clicked();

private:
    Ui::userDialog *ui;
};

#endif // USERDIALOG_H
