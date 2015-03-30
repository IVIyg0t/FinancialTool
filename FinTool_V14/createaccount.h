#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include <QString>
namespace Ui {
class createAccount;
}

class createAccount : public QDialog
{
    Q_OBJECT

public:
    explicit createAccount(QWidget *parent = 0);
    ~createAccount();

    QString getUsername();
    QString getPassword();
    QString getFirstTab();

private:
    Ui::createAccount *ui;
};

#endif // CREATEACCOUNT_H
