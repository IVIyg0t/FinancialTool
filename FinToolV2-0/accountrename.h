#ifndef ACCOUNTRENAME_H
#define ACCOUNTRENAME_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class accountRename;
}

class accountRename : public QDialog
{
    Q_OBJECT

public:
    explicit accountRename(QWidget *parent = 0);
    ~accountRename();

    QString getName();



    bool setState(bool state){
        this->state = state;
        return this->state;
    }

    //Function to return the current state of
    bool isGood(){
        return this->state;
    }

    void setTabNames(QStringList names){
        this->tabNames = names;
    }


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    bool state;
    QStringList tabNames;
    Ui::accountRename *ui;
};

#endif // ACCOUNTRENAME_H
