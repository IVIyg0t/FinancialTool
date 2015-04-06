#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T13:37:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinToolV2-0
TEMPLATE = app


SOURCES += main.cpp\
        fintool.cpp \
    login.cpp \
    createaccount.cpp \
    createfirsttabaccount.cpp \
    addtabaccount.cpp \
    addtransaction.cpp

HEADERS  += fintool.h \
    login.h \
    createaccount.h \
    createfirsttabaccount.h \
    addtabaccount.h \
    addtransaction.h

FORMS    += fintool.ui \
    login.ui \
    createaccount.ui \
    createfirsttabaccount.ui \
    addtabaccount.ui \
    addtransaction.ui
