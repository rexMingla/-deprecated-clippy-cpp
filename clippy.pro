QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clippy
TEMPLATE = app

include($$PWD/vendor/qxt/qxt.pri)
include($$PWD/src/common/common.pri)
include($$PWD/src/settings/settings.pri)
include($$PWD/src/settingsWidget/settingsWidget.pri)
include($$PWD/src/clipboard/clipboard.pri)
include($$PWD/src/os/os.pri)

!test {
  include($$PWD/src/app/app.pri)
} else {
  include($$PWD/test/test.pri)
}

macx {
    LIBS += -framework Carbon
}

INCLUDEPATH += .

RESOURCES += resources/clippy.qrc

