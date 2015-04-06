/********************************************************************************
** Form generated from reading UI file 'userdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERDIALOG_H
#define UI_USERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_userDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *createaccount;
    QPushButton *signin;

    void setupUi(QDialog *userDialog)
    {
        if (userDialog->objectName().isEmpty())
            userDialog->setObjectName(QStringLiteral("userDialog"));
        userDialog->resize(224, 171);
        gridLayout = new QGridLayout(userDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(userDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(userDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit = new QLineEdit(userDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 2);

        lineEdit_2 = new QLineEdit(userDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 3, 0, 1, 2);

        createaccount = new QPushButton(userDialog);
        createaccount->setObjectName(QStringLiteral("createaccount"));

        gridLayout->addWidget(createaccount, 9, 0, 1, 2);

        signin = new QPushButton(userDialog);
        signin->setObjectName(QStringLiteral("signin"));

        gridLayout->addWidget(signin, 4, 0, 1, 2);

        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, signin);
        QWidget::setTabOrder(signin, createaccount);

        retranslateUi(userDialog);

        QMetaObject::connectSlotsByName(userDialog);
    } // setupUi

    void retranslateUi(QDialog *userDialog)
    {
        userDialog->setWindowTitle(QApplication::translate("userDialog", "Dialog", 0));
        label->setText(QApplication::translate("userDialog", "Username", 0));
        label_2->setText(QApplication::translate("userDialog", "Password", 0));
        createaccount->setText(QApplication::translate("userDialog", "Create Account", 0));
        signin->setText(QApplication::translate("userDialog", "Sign In", 0));
    } // retranslateUi

};

namespace Ui {
    class userDialog: public Ui_userDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERDIALOG_H
