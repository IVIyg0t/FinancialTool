#ifndef FINTOOL_H
#define FINTOOL_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>
#include "addtransaction.h"
#include <QVariant>

struct inputData {
    QString Information;
    double Amount;
    QTime Time;
    QDate Date;
    QString Account;
    QString Category;
    QString transType;
    bool success;
};

namespace Ui {
class FinTool;
}

class FinTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit FinTool(QWidget *parent = 0);
    ~FinTool();

public slots:
    void on_actionadd_transaction_triggered();

private slots:

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::FinTool *ui;
};

#endif // FINTOOL_H
