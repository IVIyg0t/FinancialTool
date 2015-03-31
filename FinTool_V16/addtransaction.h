#ifndef ADDTRANSACTION_H
#define ADDTRANSACTION_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QDate>
#include <QEvent>
#include "addType.h"
#include <QStringList>
#include <QTextStream>
#include <QMessageBox>

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
  //  QString addTransaction::getAccount();
    QString addTransaction::getCategory();
    QString addTransaction::getTransactionType();
    double addTransaction::getAmount();
    QTime addTransaction::getTime();
    QDate addTransaction::getDate();

    QStringList addTransaction::genCategoryOptions();

    bool addTransaction::eventFilter(QObject *target, QEvent *event);

    ~addTransaction();

private slots:
//    void on_cb_account_currentIndexChanged(const QString &arg1);

    void on_cb_category_currentIndexChanged(const QString &arg1);

//    void on_cb_transaction_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addTransaction *ui;
    QStringList Categories;
    QStringList Transaction_types;

    QMessageBox Required_fields;
};

#endif // ADDTRANSACTION_H
