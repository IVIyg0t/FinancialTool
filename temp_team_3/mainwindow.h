#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTimeEdit>

struct Input_data {
    QString Information;
    double  Amount;
    QTime   Time;
    QDate   Date;
    QString Account;
    QString Category;
    QString Transaction_type;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_actionAdd_Entry_triggered();

private:
    Ui::MainWindow *ui;

    //Some strings that are were used for testing
    QString input_text;
    QString input_category;
    QString input_account;
};

#endif // MAINWINDOW_H
