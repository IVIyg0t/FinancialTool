#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>

namespace Ui {
class usersDialog;
}

class usersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit usersDialog(QWidget *parent = 0);
    ~usersDialog();

private:
    Ui::usersDialog *ui;
};

#endif // USERSDIALOG_H
