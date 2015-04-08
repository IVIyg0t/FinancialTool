#ifndef ADDTRANSACTION_H
#define ADDTRANSACTION_H

#include <QDialog>
#include <QString>
#include <QDate>
#include <QEvent>
#include <QStringList>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QKeyEvent>
#include <QDebug>

namespace Ui {
class addTransaction;
}

class addTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit addTransaction(QString Username, QWidget *parent = 0);
    ~addTransaction();

    //Setter functions
    void setUsername(QString Username){
        this->username = Username;
    }

    //Getting functions
    QDate getDate();
    QString getCategory();
    QString getTransactionType();
    QString getAddInfo();
    double getAmount();

    QStringList genCategoryOptions();

    bool addTransaction::eventFilter(QObject *target, QEvent *event);


private slots:
    void on_Category_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    QString username;
    QStringList categories;
    QStringList transtypes;
    Ui::addTransaction *ui;
    QMessageBox Required_Fields;
};

#endif // ADDTRANSACTION_H
