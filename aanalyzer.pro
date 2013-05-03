#-------------------------
#
# Project created by abcdw
#
#-------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aanalyzer
TEMPLATE = app


SOURCES += main.cpp\
           ui/mainwindow.cpp \
           src/parser.cpp \
           src/binarysearchtree.cpp

HEADERS  += ui/mainwindow.h \
            src/parser.h \
            src/binarysearchtree.h

FORMS    +=
