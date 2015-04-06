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

private:
    Ui::addTabAccount *ui;
};

#endif // ADDTABACCOUNT_H
