#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T13:37:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QFontIconEx
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp


include("../QFontIcon/QFontIcon.pri")

RESOURCES += \
    resource.qrc

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h
