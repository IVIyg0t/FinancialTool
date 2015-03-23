# FinancialTool
CMSC 420 Financial Tool Project


Using the cash.txt to populate with some sample data:
When you run your project, a folder will be created similar to this outside of your project files folder:
  "build-AcctMgr_V1-Desktop_Qt_5_4_1_MSVC2013_64bit-Debug"
This is where you want to place the "cash.txt" file.  You'll find the "cash.txt" that i've used inside the AcctMgr_V1.10 folder.  You need to copy/paste this into the debug folder i mentioned earlier.



Branch V1.10
<br />
Changes since V1:
<br />
1. Added functionality for importing transaction data via CSV by the function <br />
          void AcctMgr::loadInitAcct(QStandardItemModel *model) <br />
      The function looks for a file called "cash.txt" inside the debug folder for importing <br />
2. Added functionality for "add account" button via the function <br />
          void on_pushButton_clicked()<br />
      The function will take the data input in the QlineEdit and use it as the label <br />
      for the new tab.  Once the tab is created, it is automatically set as the current tab <br />
      and a QTableView is added to the "current active tab".<br />
3. Added skeleton functionality for "Add Transaction" button via function<br />
          void on_pushButton_clicked()<br />
      Once the button is clicked it will open a new dialogWindow from the "addnewtransaction" class.<br />

Still needed:<br />
1. further functionality for the "add transaction" button needs to be sorted.  We need to figure out how to send data from the QLineEdit(s) from the dialogWindow to the mainWindow to be used for importing to the QTableView of the currently active tab.
