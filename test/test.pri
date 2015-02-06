QT += testlib

TARGET = test_clippy
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(clipboard/test_clipboard.pri)

# thanks to http://qtcreator.blogspot.ca/2010/04/sample-multiple-unit-test-project.html
SOURCES += \
    test/test_main.cc \
    test/AutoTest.h
