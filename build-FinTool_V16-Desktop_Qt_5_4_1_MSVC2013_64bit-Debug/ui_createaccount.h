/********************************************************************************
** Form generated from reading UI file 'createaccount.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACCOUNT_H
#define UI_CREATEACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_createAccount
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit;

    void setupUi(QDialog *createAccount)
    {
        if (createAccount->objectName().isEmpty())
            createAccount->setObjectName(QStringLiteral("createAccount"));
        createAccount->resize(197, 212);
        gridLayout = new QGridLayout(createAccount);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(createAccount);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(createAccount);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(createAccount);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        lineEdit_3 = new QLineEdit(createAccount);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 5, 0, 1, 1);

        comboBox = new QComboBox(createAccount);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 5, 1, 1, 1);

        buttonBox = new QDialogButtonBox(createAccount);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 2);

        lineEdit_2 = new QLineEdit(createAccount);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 3, 0, 1, 2);

        lineEdit = new QLineEdit(createAccount);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 2);

        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, lineEdit_3);
        QWidget::setTabOrder(lineEdit_3, comboBox);

        retranslateUi(createAccount);
        QObject::connect(buttonBox, SIGNAL(accepted()), createAccount, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), createAccount, SLOT(reject()));

        QMetaObject::connectSlotsByName(createAccount);
    } // setupUi

    void retranslateUi(QDialog *createAccount)
    {
        createAccount->setWindowTitle(QApplication::translate("createAccount", "Dialog", 0));
        label->setText(QApplication::translate("createAccount", "Username:", 0));
        label_2->setText(QApplication::translate("createAccount", "Password:", 0));
        label_3->setText(QApplication::translate("createAccount", "Initial Bank Account:", 0));
    } // retranslateUi

};

namespace Ui {
    class createAccount: public Ui_createAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCOUNT_H
