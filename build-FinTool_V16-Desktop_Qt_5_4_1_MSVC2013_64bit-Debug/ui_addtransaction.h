/********************************************************************************
** Form generated from reading UI file 'addtransaction.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTRANSACTION_H
#define UI_ADDTRANSACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addTransaction
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_6;
    QDateTimeEdit *dte_time_date;
    QComboBox *cb_category;
    QComboBox *cb_transaction;
    QLineEdit *le_info;
    QDoubleSpinBox *dsb_amount;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;

    void setupUi(QDialog *addTransaction)
    {
        if (addTransaction->objectName().isEmpty())
            addTransaction->setObjectName(QStringLiteral("addTransaction"));
        addTransaction->resize(314, 188);
        gridLayout = new QGridLayout(addTransaction);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(addTransaction);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_6 = new QLabel(addTransaction);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        dte_time_date = new QDateTimeEdit(addTransaction);
        dte_time_date->setObjectName(QStringLiteral("dte_time_date"));

        gridLayout->addWidget(dte_time_date, 1, 0, 1, 4);

        cb_category = new QComboBox(addTransaction);
        cb_category->setObjectName(QStringLiteral("cb_category"));

        gridLayout->addWidget(cb_category, 6, 0, 1, 1);

        cb_transaction = new QComboBox(addTransaction);
        cb_transaction->setObjectName(QStringLiteral("cb_transaction"));

        gridLayout->addWidget(cb_transaction, 6, 1, 1, 1);

        le_info = new QLineEdit(addTransaction);
        le_info->setObjectName(QStringLiteral("le_info"));

        gridLayout->addWidget(le_info, 8, 0, 1, 4);

        dsb_amount = new QDoubleSpinBox(addTransaction);
        dsb_amount->setObjectName(QStringLiteral("dsb_amount"));

        gridLayout->addWidget(dsb_amount, 6, 2, 1, 2);

        pushButton = new QPushButton(addTransaction);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 9, 0, 1, 1);

        pushButton_2 = new QPushButton(addTransaction);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 9, 1, 1, 1);

        label_4 = new QLabel(addTransaction);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_5 = new QLabel(addTransaction);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 1, 1, 1);

        label_2 = new QLabel(addTransaction);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 3, 1, 1);

        QWidget::setTabOrder(dte_time_date, cb_category);
        QWidget::setTabOrder(cb_category, cb_transaction);
        QWidget::setTabOrder(cb_transaction, dsb_amount);
        QWidget::setTabOrder(dsb_amount, le_info);
        QWidget::setTabOrder(le_info, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(addTransaction);

        QMetaObject::connectSlotsByName(addTransaction);
    } // setupUi

    void retranslateUi(QDialog *addTransaction)
    {
        addTransaction->setWindowTitle(QApplication::translate("addTransaction", "Dialog", 0));
        label->setText(QApplication::translate("addTransaction", "Date & Time", 0));
        label_6->setText(QApplication::translate("addTransaction", "Additional Info", 0));
        pushButton->setText(QApplication::translate("addTransaction", "Ok", 0));
        pushButton_2->setText(QApplication::translate("addTransaction", "Cancel", 0));
        label_4->setText(QApplication::translate("addTransaction", "Category", 0));
        label_5->setText(QApplication::translate("addTransaction", "Transaction Type", 0));
        label_2->setText(QApplication::translate("addTransaction", "Amount", 0));
    } // retranslateUi

};

namespace Ui {
    class addTransaction: public Ui_addTransaction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTRANSACTION_H
