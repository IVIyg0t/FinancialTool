#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>
#include "createaccount.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    //Getter Functions
    QString getUsername();
    QString getPassword();

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

        file.close();
        //Check user crds
        if(username == creds.at(0) && password == creds.at(1))
            return true;
        else
            return false;
    }

private slots:
    void on_signin_clicked();

    void on_createaccount_clicked();

private:
    QString username, password;
    Ui::Login *ui;
};

#endif // LOGIN_H
