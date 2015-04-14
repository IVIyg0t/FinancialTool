#ifndef ACCOUNT_DELETE_H
#define ACCOUNT_DELETE_H

#include <QDialog>
#include <QMessageBox>
#include <QString>

namespace Ui {
class account_delete;
}

class account_delete : public QDialog
{
    Q_OBJECT

public:
    explicit account_delete(QWidget *parent = 0);
    ~account_delete();

    QString get_Account (void);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::account_delete *ui;
};

#endif // ACCOUNT_DELETE_H
