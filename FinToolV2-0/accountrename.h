#ifndef ACCOUNTRENAME_H
#define ACCOUNTRENAME_H

#include <QDialog>

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
private:
    Ui::accountRename *ui;
};

#endif // ACCOUNTRENAME_H
