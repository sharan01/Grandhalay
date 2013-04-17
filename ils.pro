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
    editbookwizard.cpp \
    wizards/addcopywizard.cpp

HEADERS  += \
    welcome.h \
    mainwindow.h \
    books.h \
    addbook.h \
    issuebook.h \
    admin.h \
    members.h \
    editbookwizard.h \
    wizards/addcopywizard.h

FORMS    +=

RESOURCES += \
    resources.qrc

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    addbookwizard.h

SOURCES += \
    addbookwizard.cpp

HEADERS += \
    bookinfoonline.h

SOURCES += \
    bookinfoonline.cpp

HEADERS += \
    addmemberwizard.h

SOURCES += \
    addmemberwizard.cpp

OTHER_FILES += \
    todo.txt

HEADERS += \
    issuebookwizard.h

SOURCES += \
    issuebookwizard.cpp

HEADERS += \
    connectdb.h

SOURCES += \
    connectdb.cpp
