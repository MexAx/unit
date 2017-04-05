#-------------------------------------------------
#
# Project created by QtCreator 2014-08-27T21:05:34
#
#-------------------------------------------------
include (../mysqldb/mysqldb.pri)

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = formjedmjere
TEMPLATE = app


SOURCES += main.cpp
       #mainwindow.cpp

#HEADERS  += mainwindow.h

#FORMS    += mainwindow.ui

#RESOURCES += \ Images/MyRes.qrc

#OTHER_FILES +=
target.path = $$PWD/projects/glavniracuni/
INSTALLS += target
