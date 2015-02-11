SOURCES += \
    $$PWD/qxtabstractfileloggerengine.cpp \
    $$PWD/qxtabstractiologgerengine.cpp \
    $$PWD/qxtbasicfileloggerengine.cpp \
    $$PWD/qxtbasicstdloggerengine.cpp \
    $$PWD/qxtglobalshortcut.cpp \
    $$PWD/qxtlogger.cpp \
    $$PWD/qxtloggerengine.cpp \
    $$PWD/qxtlogstream.cpp

HEADERS += \
    $$PWD/qxtabstractfileloggerengine.h \
    $$PWD/qxtbasicstdloggerengine.h \
    $$PWD/qxtbasicfileloggerengine.h \
    $$PWD/qxtglobal.h \
    $$PWD/qxtglobalshortcut_p.h \
    $$PWD/qxtglobalshortcut.h \
    $$PWD/qxtlogger_p.h \
    $$PWD/qxtlogger.h \
    $$PWD/qxtloggerengine.h \
    $$PWD/qxtlogstream_p.h \
    $$PWD/qxtlogstream.h

macx {
    SOURCES += $$PWD/qxtglobalshortcut_mac.cpp
}
win {
    SOURCES += $$PWD/qxtglobalshortcut_win.cpp
}
