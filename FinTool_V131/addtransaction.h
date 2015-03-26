#ifndef ADDTRANSACTION_H
#define ADDTRANSACTION_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QDate>
#include "addType.h"

namespace Ui {
class addTransaction;
}

class addTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit addTransaction(QWidget *parent = 0);

    //Getter functions for grabbing data from add transaction window
    QString addTransaction::getInfo();
    QString addTransaction::getAccount();
    QString addTransaction::getCategory();
    QString addTransaction::getTransactionType();
    double addTransaction::getAmount();
    QTime addTransaction::getTime();
    QDate addTransaction::getDate();

    ~addTransaction();

private slots:
    void on_cb_account_currentIndexChanged(const QString &arg1);

    void on_cb_category_currentIndexChanged(const QString &arg1);

    void on_cb_transaction_currentIndexChanged(const QString &arg1);

private:
    Ui::addTransaction *ui;
    QStringList Account;
    QStringList Categories;
    QStringList Transaction_types;
};

#endif // ADDTRANSACTION_H
