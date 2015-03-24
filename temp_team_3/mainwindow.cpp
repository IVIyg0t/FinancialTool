#include "mainwindow.h"
#include "add_entry.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Just some function calls that don't really do anything right now
    input_text = ui->lineEdit->text();
    ui->lineEdit->clear();
    input_category = ui->comboBox->currentText();
    ui->label->setText(input_category);
}

void MainWindow::on_actionAdd_Entry_triggered()
{
    //Opens the add_entry.ui
    //User can't click the other window without hitting accept/cancel
    Add_entry pop_up;
    pop_up.setModal(true);
    pop_up.exec();
}
