#include "fintool.h"
#include "ui_fintool.h"

FinTool::FinTool(QString username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinTool)
{
    ui->setupUi(this);
    setWindowTitle("Financial Tool V2.0");
    this->Username = username;
    //Connect actions
    connect(ui->actionNew_bank_account,SIGNAL(triggered()),this,SLOT(on_action_add_bank_account_triggered()));
    connect(ui->actionNew_transaction,SIGNAL(triggered()), this, SLOT(on_action_add_transaction_triggered()));

//    if(!accountsExist(this->Username)){
//        createFirstTabAccount tab;
//        if(tab.exec() == QDialog::Accepted){
//            ui->tabWidget->setTabText(1,tab.getAccountName()+" - "+tab.getAccountType());
//        }
//    }
    importTabAccount(this->Username);
    importTables(this->Username);

}

FinTool::~FinTool()
{
    delete ui;
}

void FinTool::writeTransaction(inputData transaction, QString User){

    QFile file("users/"+User+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    file.open(QIODevice::WriteOnly|QIODevice::Append);

    QTextStream out(&file);

    out << transaction.Date.toString("dd:MM:yyyy") << ",";

    if(transaction.transType != "")
        out << transaction.transType << ",";
    else
        out << "N/A,";

    if(transaction.Category != "")
        out << transaction.Category << ",";
    else
        out << "N/A,";

    if(transaction.information != "")
        out << transaction.information << ",";

    else
        out << "N/A,";

    out << transaction.Amount << "\n";

    file.close();
}





void FinTool::on_action_add_bank_account_triggered(){
    addTabAccount newtab;
    if(newtab.exec()== QDialog::Accepted){
        QTableWidget *newTable = new QTableWidget();
        formatTable(newTable);

        //Create a new QWidget and palce it in a new tab in the QTabWidget
        ui->tabWidget->addTab(new QWidget(), newtab.getAccountName()+" - "+newtab.getAccountType());

        //Create a QWidget and set it equal to the QWidget we just created
        QWidget *wgt = ui->tabWidget->widget(ui->tabWidget->count()-1);

        //Create a new Grid Layout
        QGridLayout *grid = new QGridLayout;

        //Add the table to the grid layout
        grid->addWidget(newTable);

        //Add the whole layout container into the tab's widget container
        wgt->setLayout(grid);

        //Create accountf file
        createFile("users/"+this->Username+"/"+newtab.getAccountName()+" - "+newtab.getAccountType());
    }
}

void FinTool::on_action_add_transaction_triggered(){
    addTransaction newTransaction(Username);
    if(newTransaction.exec() == QDialog::Accepted){

        this->newTransactionData.Amount = newTransaction.getAmount();
        this->newTransactionData.Category = newTransaction.getCategory();
        this->newTransactionData.Date = newTransaction.getDate();
        this->newTransactionData.information = newTransaction.getAddInfo();
        this->newTransactionData.transType = newTransaction.getTransactionType();
        this->newTransactionData.success = true;

        convertAmount();
    }
    if(this->newTransactionData.success == true){
        QTableWidget *curTable = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QTableWidget *>();
        setTransactionToCurrentTable(curTable);
        writeTransaction(this->newTransactionData,this->Username);

    }

}

void FinTool::importTabAccount(QString username){
    QDir dir("users/"+username+"/");
    QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);
    int iter = 1;
    foreach(QString file, accountList){
        if((file !="userAccount") && (file != "categories")){
            QTableWidget *newTable = new QTableWidget();

            formatTable(newTable);

            ui->tabWidget->addTab(new QWidget(), file);
            QWidget *wgt = ui->tabWidget->widget(iter);
            QGridLayout *grid = new QGridLayout;
            grid->addWidget(newTable);
            wgt->setLayout(grid);

            ui->tabWidget->setCurrentIndex(iter);
            iter++;
        }
    }
}

void FinTool::importTables(QString username){
    QString workingDir = "users/"+username+"/";
    QDir dir(workingDir);
    QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);

    foreach(QString file, accountList){
        if((file != "userAccount") &&(file != "categories")){
            QFile fp(workingDir+file);
            fp.open(QIODevice::ReadOnly);
            QTextStream in(&fp);

            while(!in.atEnd()){
                QString Line = in.readLine();
                QStringList transDeets;
                int tabindex = -1;

                transDeets.append(Line.split(','));

                for(int k = 0; k < ui->tabWidget->count(); k++){
                    if(file == ui->tabWidget->tabText(k)){
                        tabindex = k;
                        break;
                    }
                }

                QTableWidget *curTable = ui->tabWidget->widget(tabindex)->findChild<QTableWidget *>();

                this->newTransactionData.Date = QDate::fromString(transDeets.at(0),"dd:MM:yyyy");
                this->newTransactionData.transType = transDeets.at(1);
                this->newTransactionData.Category = transDeets.at(2);
                this->newTransactionData.information = transDeets.at(3);
                this->newTransactionData.Amount = transDeets.at(4).toDouble();
                //this->newTransactionData.curBalance = transDeets.at(5).toDouble();
                setTransactionToCurrentTable(curTable);

            }
        }
    }
}


void FinTool::on_tabWidget_currentChanged(int index)
{
    if(index > 0){
        QTableWidget *table = ui->tabWidget->widget(index)->findChild<QTableWidget *>();
        calcBalanceBottomTop(table);
    }
}
