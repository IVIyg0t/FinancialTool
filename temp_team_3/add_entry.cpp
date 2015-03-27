#include "add_entry.h"
#include "mainwindow.h"
#include "ui_add_entry.h"
#include <QApplication>
#include <QDebug>

#include <QDebug>

Add_entry::Add_entry(QWidget *parent) : QDialog(parent), ui(new Ui::Add_entry)
{
    ui->setupUi(this);
    this->Account = (QStringList() << (QString)""<< (QString)"Default" << (QString)"Add Account");
    this->Categories = (QStringList()<< (QString)"" << (QString)"Default" << (QString)"Add Category");
    this->Transaction_types = (QStringList()<< (QString)"" << (QString)"Withdrawl" << (QString)"Deposit");
    ui->cb_account->addItems(this->Account);
    ui->cb_category->addItems(this->Categories);
    ui->cb_transaction->addItems(this->Transaction_types);

    Required_fields.addButton((QString)"Ok",QMessageBox::AcceptRole);
    Required_fields.setWindowTitle("Error: Missing Required Fields");
}

Add_entry::~Add_entry()
{
    delete ui;
}

void Add_entry::on_pushButton_pressed()
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

    QStringList Missing_Fields;

    //I tried to find a cooler way of doing this but it seems to to be the most effiecent after perusing through the QStringList functionalities
    if(Users_data.Amount == 0.0)
        Missing_Fields << "Amount";
    if(Users_data.Account == NULL)
        Missing_Fields << "Account";
    if(Users_data.Category == NULL)
        Missing_Fields <<"Category";
    if(Users_data.Transaction_type == NULL)
        Missing_Fields << "Transaction_type";

    //adds the new account name below the presets and above the add account item
    if(!this->Account.contains(ui->cb_account->currentText(), Qt::CaseInsensitive))
    {
        this->Account += ui->cb_account->currentText();
        ui->cb_account->insertItem((ui->cb_account->findText("Add Account")),ui->cb_account->currentText()); //replace the first argument with zero if you want it to prepend to the combobox
    }

    //adds the new category name below the presets and above the add category item
    if(!this->Categories.contains(ui->cb_category->currentText(), Qt::CaseInsensitive))
    {
        this->Categories += ui->cb_category->currentText();
        ui->cb_category->insertItem((ui->cb_category->findText("Add Category")),ui->cb_category->currentText()); //replace the first argument with zero if you want it to prepend to the combobox
    }

    if(Users_data.Amount != 0.0 && !Missing_Fields.contains(NULL,Qt::CaseInsensitive))
    {
        ui->cb_account->setCurrentIndex(0); //resets the combo box to the first choice
        ui->cb_category->setCurrentIndex(0); //resets the combo box to the first choice
        ui->cb_transaction->setCurrentIndex(0); //resets the combo box to the first choice
        close();
    }
    else
    {
        Required_fields.setText("Please enter the following fields: "+Missing_Fields.join(',')+".");
        Required_fields.show();
    }

    //Should now call the function to display all the data in the correct fields/tabs
    //The function should recieve an Input_data struct
}

void Add_entry::on_pushButton_2_pressed()
{
    ui->cb_account->setCurrentIndex(0); //resets the combo box to the first choice
    ui->cb_category->setCurrentIndex(0); //resets the combo box to the first choice
    ui->cb_transaction->setCurrentIndex(0); //resets the combo box to the first choice
    close();
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

void Add_entry::on_cb_category_currentIndexChanged(const QString &arg1)
{
    if(arg1 == QString("Add Category"))
    {
        ui->cb_category->setEditable(true);
        ui->cb_category->clearEditText();
    }
    else if (this->Categories.contains(arg1, Qt::CaseInsensitive))
        ui->cb_category->setEditable(false);
}
