QT += testlib

TARGET = test_clippy
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(clipboard/test_clipboard.pri)
include(settings/test_settings.pri)

# thanks to http://qtcreator.blogspot.ca/2010/04/sample-multiple-unit-test-project.html
SOURCES += \
    $$PWD/test_main.cc \
    $$PWD/AutoTest.h

# http://stackoverflow.com/questions/4483370/qt-and-gcov-coverage-files-are-not-generated
#LIBS += -lgcov
#QMAKE_CXXFLAGS += -g -fprofile-arcs -ftest-coverage -O0
#QMAKE_LFLAGS += -g -fprofile-arcs -ftest-coverage  -O0
