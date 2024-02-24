include(gtest_dependency.pri)

QT += gui

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread




SOURCES += \
    ../layerdrawer.cpp \
        main.cpp \
        tst_linetest.cpp \

HEADERS += \
    ../layerdrawer.h
