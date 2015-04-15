#ifndef ADDTABACCOUNT_H
#define ADDTABACCOUNT_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QDate>
#include <QEvent>
#include <QStringList>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class addTabAccount;
}

class addTabAccount : public QDialog
{
    Q_OBJECT

public:
    explicit addTabAccount(QWidget *parent = 0);
    ~addTabAccount();


    //Getter Functions
    QString getAccountName();
    QString getAccountType();

    bool setState(bool state){
        this->state = state;
        return this->state;
    }

    bool isGood(){
        return this->state;
    }

    void setTabNames(QStringList names){
        this->tabNames = names;
    }

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    bool state;
    QStringList tabNames;
    Ui::addTabAccount *ui;
    QMessageBox string_not_found;
};

#endif // ADDTABACCOUNT_H
