#ifndef ADDTYPE_H
#define ADDTYPE_H

#include <QDialog>
#include <QEvent>
#include <QObject>
#include <QKeyEvent>


namespace Ui {
class addType;
}

class addType : public QDialog
{
    Q_OBJECT

public:


    explicit addType(QWidget *parent = 0);
    QString addType::getText();
    QString addType::getAccountType();
    ~addType();

private:
    QStringList Account;
    Ui::addType *ui;
};

#endif // ADDTYPE_H
