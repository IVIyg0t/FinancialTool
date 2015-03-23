#ifndef ACCTMGR_H
#define ACCTMGR_H

#include "addnewtransaction.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>

namespace Ui {
class AcctMgr;
}

class AcctMgr : public QMainWindow
{
    Q_OBJECT

public:
    explicit AcctMgr(QWidget *parent = 0);
    ~AcctMgr();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AcctMgr *ui;
    addNewTransaction *addTrans;
    int newTabIndex = 0;

    void AcctMgr::loadInitAcct(QStandardItemModel *model);
};

#endif // ACCTMGR_H
