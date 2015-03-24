#include "add_entry.h"
#include "mainwindow.h"
#include "ui_add_entry.h"
#include <QApplication>

Add_entry::Add_entry(QWidget *parent) : QDialog(parent), ui(new Ui::Add_entry)
{
    ui->setupUi(this);
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

    //Should now call the function to display all the data in the correct fields/tabs
    //The function should recieve an Input_data struct
}
