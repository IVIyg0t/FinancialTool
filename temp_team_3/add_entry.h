#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include <QDialog>
#include <QDateTimeEdit>


namespace Ui {
class Add_entry;
}

class Add_entry : public QDialog
{
    Q_OBJECT

public:
    explicit Add_entry(QWidget *parent = 0);
    ~Add_entry();

private slots:
    void on_buttonBox_accepted();
    void on_cb_account_currentIndexChanged(const QString &arg1);

private:
    Ui::Add_entry *ui;
    QStringList Account;
    QStringList Categories;
};

#endif // ADD_ENTRY_H
