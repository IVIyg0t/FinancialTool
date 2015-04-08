#include "fintool.h"
#include "ui_fintool.h"

FinTool::FinTool(QString username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinTool)
{
    ui->setupUi(this);
    setWindowTitle("Financial Tool V2.0");
    this->Username = username;



    // Set to and from dates to today's date
    ui->irtodate->setDate(QDate::currentDate());
    ui->irfromdate->setDate(QDate::currentDate());
    ui->srtodate->setDate(QDate::currentDate());
    ui->srfromdate->setDate(QDate::currentDate());
    ui->satodate->setDate(QDate::currentDate());
    ui->safromdate->setDate(QDate::currentDate());

    //Allow calendar pop up on QDateEdits
    ui->irtodate->setCalendarPopup(true);
    ui->irfromdate->setCalendarPopup(true);
    ui->srtodate->setCalendarPopup(true);
    ui->srfromdate->setCalendarPopup(true);
    ui->satodate->setCalendarPopup(true);
    ui->safromdate->setCalendarPopup(true);

    // Set columns for tables
    ui->balancereport->setColumnCount(2);
    ui->incomereport->setColumnCount(3);
    ui->spendingreport->setColumnCount(4);
    ui->spendinganalysis->setColumnCount(3);

    // Set column tables for tables
    ui->balancereport->setHorizontalHeaderItem(0, new QTableWidgetItem("Account Name"));
    ui->balancereport->setHorizontalHeaderItem(1, new QTableWidgetItem("Balance"));

    ui->incomereport->setHorizontalHeaderItem(0, new QTableWidgetItem("Category"));
    ui->incomereport->setHorizontalHeaderItem(1, new QTableWidgetItem("Amount"));
    ui->incomereport->setHorizontalHeaderItem(2, new QTableWidgetItem("Date"));

    ui->spendingreport->setHorizontalHeaderItem(0, new QTableWidgetItem("Category"));
    ui->spendingreport->setHorizontalHeaderItem(1, new QTableWidgetItem("Info"));
    ui->spendingreport->setHorizontalHeaderItem(2, new QTableWidgetItem("Amount"));
    ui->spendingreport->setHorizontalHeaderItem(3, new QTableWidgetItem("Date"));

    ui->spendinganalysis->setHorizontalHeaderItem(0, new QTableWidgetItem("Category"));
    ui->spendinganalysis->setHorizontalHeaderItem(1, new QTableWidgetItem("Amount"));
    ui->spendinganalysis->setHorizontalHeaderItem(2, new QTableWidgetItem("Percentage"));


    //Connect actions
    connect(ui->actionNew_bank_account,SIGNAL(triggered()),this,SLOT(on_action_add_bank_account_triggered()));
    connect(ui->actionNew_transaction,SIGNAL(triggered()), this, SLOT(on_action_add_transaction_triggered()));

    connect(ui->irfromdate,SIGNAL(editingFinished()),this,SLOT(on_date_changed()));
    connect(ui->irtodate,SIGNAL(editingFinished()),this,SLOT(on_date_changed()));

    connect(ui->srfromdate,SIGNAL(editingFinished()),this, SLOT(on_date_changed()));
    connect(ui->srtodate,SIGNAL(editingFinished()),this,SLOT(on_date_changed()));

    connect(ui->safromdate,SIGNAL(editingFinished()),this,SLOT(on_date_changed()));
    connect(ui->satodate,SIGNAL(editingFinished()),this,SLOT(on_date_changed()));

    // If the current user has account files in their user folder, then import them
    if(accountsExist(this->Username)){
        importTabAccount(this->Username);
        importTables(this->Username);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else{     //Else let's display that there is nothing to show in the reports
        ui->stackedWidget->setCurrentIndex(0);
    }
}

FinTool::~FinTool()
{
    delete ui;
}

void FinTool::on_date_changed(){
    genIncomeReport();
    genSpendingAnalysisReport();
}

//Function to generate balance report
void FinTool::genBalanceReport(){
    ui->balancereport->setRowCount(0);
    // loop through tabs
    for(int i = 1; i < ui->tabWidget->count(); i++){
       QTableWidget *curTable = ui->tabWidget->widget(i)->findChild<QTableWidget *>();
        if(!curTable->rowCount() == 0){
            if(ui->balancereport->rowCount() <= ui->tabWidget->count()-1)
        ui->balancereport->insertRow(0);

       //Loop through the columns of first row
        ui->balancereport->setItem(0,1, new QTableWidgetItem(curTable->item(0,5)->text()));
        ui->balancereport->setItem(0,0, new QTableWidgetItem(ui->tabWidget->tabText(i)));

        }
}

    ui->balancereport->insertRow(ui->balancereport->rowCount());
    ui->balancereport->insertRow(ui->balancereport->rowCount());
    ui->balancereport->setItem(ui->balancereport->rowCount()-1,0, new QTableWidgetItem("Total"));
    double sum = 0;
    int rowCount = ui->balancereport->rowCount();
    for(int i = 0; i < rowCount-2; i++){
        sum += ui->balancereport->item(i,1)->text().toDouble();
    }
    ui->balancereport->setItem(ui->balancereport->rowCount()-1,1,new QTableWidgetItem(QString::number(sum)));
    QFont font;
    font.setBold(true);
    ui->balancereport->item(ui->balancereport->rowCount()-1,0)->setFont(font);
    ui->balancereport->item(ui->balancereport->rowCount()-1,1)->setFont(font);
}

void FinTool::genIncomeReport(){
    ui->incomereport->setRowCount(0);
    ui->spendingreport->setRowCount(0);

    QDate incomeFrom = ui->irfromdate->date();
    QDate incomeTo = ui->irtodate->date();
    QDate spendingFrom = ui->srfromdate->date();
    QDate spendingTo = ui->srtodate->date();

    //Loop through tabs
    for(int i = 1; i < ui->tabWidget->count(); i++){
        QTableWidget *curTable = ui->tabWidget->widget(i)->findChild<QTableWidget *>();

        //if(ui->incomereport->rowCount() <= ui->tabWidget->count()-1)
        //    ui->incomereport->insertRow(0);

        // Cycle through each Row of the current Table
        for(int j = 0; j < curTable->rowCount(); j++){
            if(curTable->item(j,1)->text() == "Income"){
                if( (incomeFrom <= QDate::fromString(curTable->item(j,0)->text(),"M/d/yyyy")) && (incomeTo >= QDate::fromString(curTable->item(j,0)->text(),"M/d/yyyy"))){
                    ui->incomereport->insertRow(0);
                    ui->incomereport->setItem(0,0, new QTableWidgetItem(curTable->item(j,2)->text()));
                    ui->incomereport->setItem(0,1, new QTableWidgetItem(curTable->item(j,4)->text()));
                    ui->incomereport->setItem(0,2, new QTableWidgetItem(curTable->item(j,0)->text()));
                }
            }
            if(curTable->item(j,1)->text() == "Expense"){
                if( (spendingFrom <= QDate::fromString(curTable->item(j,0)->text(),"M/d/yyyy")) && (spendingTo >= QDate::fromString(curTable->item(j,0)->text(), "M/d/yyyy"))){
                    ui->spendingreport->insertRow(0);
                    ui->spendingreport->setItem(0,0, new QTableWidgetItem(curTable->item(j,2)->text()));
                    ui->spendingreport->setItem(0,1, new QTableWidgetItem(curTable->item(j,3)->text()));
                    ui->spendingreport->setItem(0,2, new QTableWidgetItem(QString::number(curTable->item(j,4)->text().toDouble()*-1)));
                    ui->spendingreport->setItem(0,3, new QTableWidgetItem(curTable->item(j,0)->text()));
                }
            }
        }
    }
    double sum = 0;
    double sum2 = 0;
    ui->incomereport->insertRow(ui->incomereport->rowCount());
    ui->incomereport->insertRow(ui->incomereport->rowCount());

    ui->spendingreport->insertRow(ui->spendingreport->rowCount());
    ui->spendingreport->insertRow(ui->spendingreport->rowCount());


    for(int j = 0; j < ui->incomereport->rowCount()-2; j++){
        sum += ui->incomereport->item(j,1)->text().toDouble();
    }
    for(int j = 0; j < ui->spendingreport->rowCount()-2; j++)
        sum2 += ui->spendingreport->item(j,2)->text().toDouble();

    ui->incomereport->setItem(ui->incomereport->rowCount()-1, 0, new QTableWidgetItem("Total Income"));
    ui->incomereport->setItem(ui->incomereport->rowCount()-1, 1, new QTableWidgetItem(QString::number(sum)));

    ui->spendingreport->setItem(ui->spendingreport->rowCount()-1,0, new QTableWidgetItem("Total Expenditures"));
    ui->spendingreport->setItem(ui->spendingreport->rowCount()-1,2, new QTableWidgetItem(QString::number(sum2)));
    QFont font;
    font.setBold(true);
    ui->incomereport->item(ui->incomereport->rowCount()-1,0)->setFont(font);
    ui->incomereport->item(ui->incomereport->rowCount()-1,1)->setFont(font);
    ui->spendingreport->item(ui->spendingreport->rowCount()-1,0)->setFont(font);
    ui->spendingreport->item(ui->spendingreport->rowCount()-1,2)->setFont(font);

}

// Function to generate expense reports
void FinTool::genSpendingAnalysisReport(){
    ui->spendinganalysis->setRowCount(0);

    QFile file("users/"+this->Username+"/categories");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList cats;
    cats.append(line.split(','));
    QVector<double> sum(cats.size());
    double buf;

    //Loop thorugh tabs
    for(int i = 1; i < ui->tabWidget->count(); i++){

        QTableWidget *curTable = ui->tabWidget->widget(i)->findChild<QTableWidget *>();
        int k = 0;
        foreach(QString cat, cats){
            buf = 0;
            for(int j = 0; j < curTable->rowCount(); j++){
                if((curTable->item(j, 1)->text() == "Expense") && (curTable->item(j, 2)->text() == cat)){
                   buf += curTable->item(j,4)->text().toDouble();
                }
            }

            sum[k] += buf;
            k++;
        }
    }
    int k = 0;
    double total = 0;
    foreach(QString cat, cats){
        ui->spendinganalysis->insertRow(0);
        ui->spendinganalysis->setItem(0,0, new QTableWidgetItem(cat));
        ui->spendinganalysis->setItem(0,1, new QTableWidgetItem(QString::number(sum.at(k)*-1)));
        total += sum.at(k);
        k++;
    }

    //ui->spendinganalysis->insertRow(ui->spendinganalysis->rowCount());
    //ui->spendinganalysis->insertRow(ui->spendinganalysis->rowCount());
    ui->spendinganalysis->setItem(ui->spendinganalysis->rowCount()-1, 0, new QTableWidgetItem("Total Expenditures"));
    ui->spendinganalysis->setItem(ui->spendinganalysis->rowCount()-1, 1, new QTableWidgetItem(QString::number(total*-1)));

    QFont font;
    font.setBold(true);
    ui->spendinganalysis->item(ui->spendinganalysis->rowCount()-1,0)->setFont(font);
    ui->spendinganalysis->item(ui->spendinganalysis->rowCount()-1,1)->setFont(font);

    for(int j = 0; j < ui->spendinganalysis->rowCount()-1; j++){
        ui->spendinganalysis->setItem(j,2, new QTableWidgetItem(QString::number(ui->spendinganalysis->item(j,1)->text().toInt()/(total*-1)*100,'f',0)+"%"));
    }
}

//Function to filter operations when enter or return is presured while editing some cells
bool FinTool::eventFilter(QObject *target, QEvent *event){
    QString curType;
    //QComboBox combo = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QComboBox *>();
    QTableWidget *curTable = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QTableWidget *>();
    QModelIndex ind = curTable->model()->index(this->curComboRow,2);
    QComboBox *curCombo = qobject_cast<QComboBox *>(curTable->indexWidget(ind));

    if(target == curCombo){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if((keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return)){
                curType = curCombo->currentText();
                curTable->removeCellWidget(this->curComboRow,2);
                curTable->setItem(this->curComboRow,2, new QTableWidgetItem(curType));
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(target,event);
}


/*
 * Functions meant for writing to files
 *
 */
void FinTool::rewriteTableToFile(QTableWidget *curTable){
    delFile("users/"+this->Username+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    QFile file("users/"+this->Username+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    int row = curTable->rowCount();
    int column = curTable->columnCount();

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(curTable->item(i,j)->text() == "")
                out << "N/A,";
            else if(j < 5)
                out << curTable->item(i,j)->text() << ",";
            else
                out << curTable->item(i,j)->text();

        }
        out << "\n";
    }
    file.close();
}


void FinTool::writeTransaction(inputData transaction, QString User){

    QFile file("users/"+User+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    file.open(QIODevice::WriteOnly|QIODevice::Append);

    QTextStream out(&file);

    out << transaction.Date.toString("M/d/yyyy") << ",";

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

void FinTool::editTransactionFileAmount(QString edit, int totalRow, int row, int column){
    QFile file("users/"+this->Username+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    int lineIndex = totalRow - row;
    int i = 0;
    while(!in.atEnd()){
        QString line = in.readLine();
        i++;
    }

    QVector<QStringList> data(i);

    in.seek(0);
    i = 0;
    while(!in.atEnd()){
        QString line = in.readLine();
        data[i].append(line.split(','));
        i++;
    }

    QStringList slist = data.at(lineIndex-1);
    slist.replace(column, edit);
    data.replace(lineIndex-1,slist);
    file.close();

    delFile("users/"+this->Username+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    QFile ofile("users/"+this->Username+"/"+ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    ofile.open(QIODevice::WriteOnly);
    QTextStream out(&ofile);
    for(int j = 0; j < totalRow; j++){
        QString line = data.at(j).join(',');
        out << line << "\n";
    }

    ofile.close();

}

// End of functions meant for writing to files


/*
 *  All Slot Functions
 */


void FinTool::cellMenu(const QPoint &pos){
    QMenu menu(this);
    QTableWidget *curTable = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QTableWidget *>();
    QAction *u = menu.addAction("Remove Row");
    QAction *a = menu.exec(curTable->viewport()->mapToGlobal(pos));
    if(a == u){
        curTable->removeRow(curTable->currentRow());
        calcBalanceBottomTop(curTable);
        rewriteTableToFile(curTable);
    }
}


void FinTool::on_reports_addbankaccount_clicked()
{
    addTabAccount newtab;
    if(newtab.exec()== QDialog::Accepted){
        QTableWidget *newTable = createTable();
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

        ui->stackedWidget->setCurrentIndex(1);
        ui->tabWidget->setCurrentIndex(1);
    }
}



void FinTool::on_action_add_bank_account_triggered(){
    addTabAccount newtab;
    if(newtab.exec()== QDialog::Accepted){
        QTableWidget *newTable = createTable();
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

        if(this->newTransactionData.success == true){
            if(ui->tabWidget->count() > 1){
                QTableWidget *curTable = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QTableWidget *>();
                curTable->blockSignals(true);
                setTransactionToCurrentTable(curTable);
                curTable->blockSignals(false);
                writeTransaction(this->newTransactionData,this->Username);
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
    else{
        genBalanceReport();
        genIncomeReport();
        genSpendingAnalysisReport();
    }
}


void FinTool::on_cell_item_changed(int row, int column){
    QTableWidget *curTable = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QTableWidget *>();
    if(column == 1){
        curTable->blockSignals(true);
        QString lastTranType;
        QString transType = curTable->item(row,1)->text();

        if(curTable->item(row,4)->text().toDouble() < 0)
            lastTranType = "Expense";
        else
            lastTranType = "Income";

        if(transType == "income"){
            transType = "Income";
            curTable->setItem(row,1, new QTableWidgetItem("Income"));
        }
        else if(transType == "expense"){
            transType = "Expense";
            curTable->setItem(row,1, new QTableWidgetItem("Expense"));
        }
        else if((transType != "Expense") && (transType != "Income") && (transType != "expense") && (transType != "income")){
            curTable->setItem(row,1, new QTableWidgetItem(lastTranType));
            QMessageBox badTransType;
            badTransType.setText("The transaction type is invalid, please type either 'Income' or 'Expense'");
            badTransType.exec();
        }
        double amount = curTable->item(row,4)->text().toDouble();
        if((lastTranType == "Income") ^ (transType == "Income"))
            amount = amount * -1;

        curTable->setItem(row,4, new QTableWidgetItem(QString::number(amount)));

        curTable->blockSignals(false);
        calcBalanceBottomTop(curTable);
    }
    else if(column == 2){
        editTransactionFileAmount(curTable->item(row,column)->text(),curTable->rowCount(),row,column);
    }
    else if(column == 4){
        QString transType = curTable->item(row,1)->text();
        double amount = curTable->item(row,4)->text().toDouble();

        curTable->blockSignals(true);

        if(transType == "Expense" && amount > 0)
            amount = amount *-1;
        else if(transType == "Income" && amount < 0)
            amount = amount*-1;
        curTable->setItem(row,4, new QTableWidgetItem(QString::number(amount)));

        curTable->blockSignals(false);

        calcBalanceBottomTop(curTable);
        editTransactionFileAmount(QString::number(amount),curTable->rowCount(),row,column);
    }
}

void FinTool::on_cell_item_doubleclicked(int row, int column){
    this->curComboRow = row;
    this->curComboColumn = column;
    if(column == 2){
        QTableWidget *curTable = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QTableWidget *>();
        QComboBox *combo = new QComboBox();
        combo->addItems(genCategoryOptions());
        combo->installEventFilter(this);
        curTable->setCellWidget(row,column,combo);
    }
}
// END Slot functions


/*
 * Functions for importing existing user data
 */

void FinTool::importTabAccount(QString username){
    QDir dir("users/"+username+"/");
    QStringList accountList = dir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);
    int iter = 1;
    foreach(QString file, accountList){
        if((file !="userAccount") && (file != "categories")){
            QTableWidget *newTable = createTable();
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
                curTable->blockSignals(true);
                this->newTransactionData.Date = QDate::fromString(transDeets.at(0),"M/d/yyyy");
                this->newTransactionData.transType = transDeets.at(1);
                this->newTransactionData.Category = transDeets.at(2);
                this->newTransactionData.information = transDeets.at(3);
                this->newTransactionData.Amount = transDeets.at(4).toDouble();
                //this->newTransactionData.curBalance = transDeets.at(5).toDouble();
                setTransactionToCurrentTable(curTable);
                curTable->blockSignals(false);

            }
        }
    }
}

//End Functions for importing existing user data

