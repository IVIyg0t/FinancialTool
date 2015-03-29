#ifndef FINTOOL_H
#define FINTOOL_H

#include <QMainWindow>
#include "addtransaction.h"
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDir>

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
    bool fileExists(QString path);
    bool userDirExists();
    void createUsersDir();
    void fileCreate(QString name);
    void createDir(QString name);
    void writeString(QString fileName, QString info);
    void writeTransaction(inputData transaction);


public slots:
    void on_actionadd_transaction_triggered();

private:
    Ui::FinTool *ui;
};

#endif // FINTOOL_H
