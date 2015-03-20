#ifndef ACCTMGR_H
#define ACCTMGR_H

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


private:
    Ui::AcctMgr *ui;
};

#endif // ACCTMGR_H
