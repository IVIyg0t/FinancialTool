#include "add_entry.h"
#include "mainwindow.h"
#include "ui_add_entry.h"
#include <QApplication>

#include <QDebug>

Add_entry::Add_entry(QWidget *parent) : QDialog(parent), ui(new Ui::Add_entry)
{
    ui->setupUi(this);
    this->Account = (QStringList()<< (QString)"Default" << (QString)"Add Account");
    this->Categories = (QStringList()<< (QString)"Default" << (QString)"Add Category");
    ui->cb_account->addItems(this->Account);
}

Add_entry::~Add_entry()
{
    delete ui;
}

void Add_entry::on_buttonBox_accepted()
{
    Input_data Users_data;
    //After hitting accept to adding a new entry all data is imported into a global structure
    Users_data.Information = ui->le_info->text();
    Users_data.Amount = ui->dsb_amount->value();
    Users_data.Account = ui->cb_account->currentText();
    Users_data.Category = ui->cb_category->currentText();
    Users_data.Transaction_type = ui->cb_transaction->currentText();
    Users_data.Time = ui->dte_time_date->time();
    Users_data.Date = ui->dte_time_date->date();

    //adds the new account name below the presets and above the add account item
    if(!this->Account.contains(ui->cb_account->currentText(), Qt::CaseInsensitive))
    {
        this->Account += ui->cb_account->currentText();
        ui->cb_account->insertItem((ui->cb_account->findText("Add Account")),ui->cb_account->currentText()); //replace the first argument with zero if you want it to prepend to the combobox
    }

    ui->cb_account->setCurrentIndex(0); //resets the combo box to the first choice

    //Should now call the function to display all the data in the correct fields/tabs
    //The function should recieve an Input_data struct
}

void Add_entry::on_cb_account_currentIndexChanged(const QString &arg1)
{
    if(arg1 == QString("Add Account"))
    {
        ui->cb_account->setEditable(true);
        ui->cb_account->clearEditText();
    }
    else if (this->Account.contains(arg1, Qt::CaseInsensitive))
        ui->cb_account->setEditable(false);
}
