#ifndef CREATEFIRSTTABACCOUNT_H
#define CREATEFIRSTTABACCOUNT_H

#include <QDialog>
#include <QString>

namespace Ui {
class createFirstTabAccount;
}

class createFirstTabAccount : public QDialog
{
    Q_OBJECT

public:
    explicit createFirstTabAccount(QWidget *parent = 0);
    ~createFirstTabAccount();

    QString getAccountName();
    QString getAccountType();

private:
    Ui::createFirstTabAccount *ui;
};

#endif // CREATEFIRSTTABACCOUNT_H
