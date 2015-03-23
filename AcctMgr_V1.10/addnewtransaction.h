#ifndef ADDNEWTRANSACTION_H
#define ADDNEWTRANSACTION_H

#include <QDialog>
#include <QString>
//#include <QStringStream>

namespace Ui {
class addNewTransaction;
}

class addNewTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit addNewTransaction(QWidget *parent = 0);
    QStringList grabTransData();
    ~addNewTransaction();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addNewTransaction *ui;
};

#endif // ADDNEWTRANSACTION_H
