/********************************************************************************
** Form generated from reading UI file 'fintool.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINTOOL_H
#define UI_FINTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FinTool
{
public:
    QAction *actionTransaction;
    QAction *actionAccount;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuFinancial_Tool_V1_4;
    QMenu *menuAdd;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FinTool)
    {
        if (FinTool->objectName().isEmpty())
            FinTool->setObjectName(QStringLiteral("FinTool"));
        FinTool->resize(783, 446);
        actionTransaction = new QAction(FinTool);
        actionTransaction->setObjectName(QStringLiteral("actionTransaction"));
        actionAccount = new QAction(FinTool);
        actionAccount->setObjectName(QStringLiteral("actionAccount"));
        centralWidget = new QWidget(FinTool);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableWidget = new QTableWidget(tab);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        FinTool->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FinTool);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 783, 21));
        menuFinancial_Tool_V1_4 = new QMenu(menuBar);
        menuFinancial_Tool_V1_4->setObjectName(QStringLiteral("menuFinancial_Tool_V1_4"));
        menuAdd = new QMenu(menuBar);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        FinTool->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FinTool);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FinTool->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FinTool);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FinTool->setStatusBar(statusBar);

        menuBar->addAction(menuFinancial_Tool_V1_4->menuAction());
        menuBar->addAction(menuAdd->menuAction());
        menuAdd->addAction(actionTransaction);
        menuAdd->addAction(actionAccount);

        retranslateUi(FinTool);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FinTool);
    } // setupUi

    void retranslateUi(QMainWindow *FinTool)
    {
        FinTool->setWindowTitle(QApplication::translate("FinTool", "FinTool", 0));
        actionTransaction->setText(QApplication::translate("FinTool", "Transaction", 0));
        actionAccount->setText(QApplication::translate("FinTool", "Account", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("FinTool", "Tab 1", 0));
        menuFinancial_Tool_V1_4->setTitle(QApplication::translate("FinTool", "Financial Tool V1.6", 0));
        menuAdd->setTitle(QApplication::translate("FinTool", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class FinTool: public Ui_FinTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINTOOL_H
