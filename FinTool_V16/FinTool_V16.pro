#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T14:26:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinTool_V14
TEMPLATE = app


SOURCES += main.cpp\
        fintool.cpp \
    userdialog.cpp \
    createaccount.cpp \
    addtransaction.cpp \
    addtype.cpp

HEADERS  += fintool.h \
    userdialog.h \
    createaccount.h \
    addtransaction.h \
    addtype.h

FORMS    += fintool.ui \
    userdialog.ui \
    createaccount.ui \
    addtransaction.ui \
    addtype.ui
