#-------------------------------------------------
#
# Project created by QtCreator 2022-10-10T14:36:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test_porgramm
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    createnewfile.cpp \
    aboutprogramm.cpp \
    helpwindow.cpp

HEADERS  += mainwindow.h \
    createnewfile.h \
    aboutprogramm.h \
    helpwindow.h

FORMS    += mainwindow.ui \
    createnewfile.ui \
    aboutprogramm.ui \
    helpwindow.ui

TRANSLATIONS = QtLanguage_ru.ts \
                QtLanguage_en.ts

RESOURCES += \
    resourse.qrc
