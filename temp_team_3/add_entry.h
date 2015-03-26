#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include <QDialog>
#include <QDateTimeEdit>
#include <QMessageBox>


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
    //used to allow for user input in the category and account type
    void on_cb_account_currentIndexChanged(const QString &arg1);
    void on_cb_category_currentIndexChanged(const QString &arg1);

    //used for accept/cancel
    void on_pushButton_pressed();
    void on_pushButton_2_pressed();

private:
    Ui::Add_entry *ui;
    QStringList Account;
    QStringList Categories;
    QStringList Transaction_types;

    QMessageBox Required_fields;
};

#endif // ADD_ENTRY_H
