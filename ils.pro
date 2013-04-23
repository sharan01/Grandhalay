#-------------------------------------------------
#
# Project created by QtCreator 2013-01-18T21:48:15
#
#-------------------------------------------------

QT       +=  core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ils
TEMPLATE = app


SOURCES += main.cpp \
    welcome.cpp \
    mainwindow.cpp \
    books.cpp \
    addbook.cpp \
    issuebook.cpp \
    admin.cpp \
    members.cpp \
    wizards/editbookwizard.cpp \
    wizards/addcopywizard.cpp \
    wizards/returnbookwizarad.cpp \
    wizards/summarywizard.cpp

HEADERS  += \
    welcome.h \
    mainwindow.h \
    books.h \
    addbook.h \
    issuebook.h \
    admin.h \
    members.h \
    wizards/editbookwizard.h \
    wizards/addcopywizard.h \
    wizards/returnbookwizarad.h \
    wizards/summarywizard.h

FORMS    +=

RESOURCES += \
    resources.qrc

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    wizards/addbookwizard.h

SOURCES += \
    wizards/addbookwizard.cpp

HEADERS += \
    wizards/bookinfoonline.h

SOURCES += \
    wizards/bookinfoonline.cpp

HEADERS += \
    wizards/addmemberwizard.h

SOURCES += \
    wizards/addmemberwizard.cpp

OTHER_FILES += \
    todo.txt

HEADERS += \
    wizards/issuebookwizard.h

SOURCES += \
    wizards/issuebookwizard.cpp

HEADERS += \
    connectdb.h

SOURCES += \
    connectdb.cpp
