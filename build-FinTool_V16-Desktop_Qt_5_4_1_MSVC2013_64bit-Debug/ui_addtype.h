/********************************************************************************
** Form generated from reading UI file 'addtype.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTYPE_H
#define UI_ADDTYPE_H

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

class Ui_addType
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *addType)
    {
        if (addType->objectName().isEmpty())
            addType->setObjectName(QStringLiteral("addType"));
        addType->resize(249, 86);
        gridLayout = new QGridLayout(addType);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(addType);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(addType);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        lineEdit = new QLineEdit(addType);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        comboBox = new QComboBox(addType);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(addType);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        QWidget::setTabOrder(lineEdit, comboBox);

        retranslateUi(addType);
        QObject::connect(buttonBox, SIGNAL(accepted()), addType, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), addType, SLOT(reject()));

        QMetaObject::connectSlotsByName(addType);
    } // setupUi

    void retranslateUi(QDialog *addType)
    {
        addType->setWindowTitle(QApplication::translate("addType", "Dialog", 0));
        label->setText(QApplication::translate("addType", "Account Name", 0));
        label_2->setText(QApplication::translate("addType", "Account Type", 0));
    } // retranslateUi

};

namespace Ui {
    class addType: public Ui_addType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTYPE_H
