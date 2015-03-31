#include "usersdialog.h"
#include "ui_usersdialog.h"

usersDialog::usersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usersDialog)
{
    ui->setupUi(this);
}

usersDialog::~usersDialog()
{
    delete ui;
}
