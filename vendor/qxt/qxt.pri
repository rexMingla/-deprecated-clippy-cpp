SOURCES += \
    vendor/qxt/qxtabstractfileloggerengine.cpp \
    vendor/qxt/qxtabstractiologgerengine.cpp \
    vendor/qxt/qxtbasicfileloggerengine.cpp \
    vendor/qxt/qxtbasicstdloggerengine.cpp \
    vendor/qxt/qxtglobalshortcut.cpp \
    vendor/qxt/qxtlogger.cpp \
    vendor/qxt/qxtloggerengine.cpp \
    vendor/qxt/qxtlogstream.cpp

HEADERS += \
    vendor/qxt/qxtabstractfileloggerengine.h \
    vendor/qxt/qxtbasicstdloggerengine.h \
    vendor/qxt/qxtbasicfileloggerengine.h \
    vendor/qxt/qxtglobal.h \
    vendor/qxt/qxtglobalshortcut_p.h \
    vendor/qxt/qxtglobalshortcut.h \
    vendor/qxt/qxtlogger_p.h \
    vendor/qxt/qxtlogger.h \
    vendor/qxt/qxtloggerengine.h \
    vendor/qxt/qxtlogstream_p.h \
    vendor/qxt/qxtlogstream.h

macx {
    SOURCES += vendor/qxt/qxtglobalshortcut_mac.cpp
}
win {
    SOURCES += vendor/qxt/qxtglobalshortcut_win.cpp
}
