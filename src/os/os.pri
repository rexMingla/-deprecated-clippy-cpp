SOURCES += \
    $$PWD/OsManager.cc \
    $$PWD/Process.cc

HEADERS += \
    $$PWD/OsManager.h \
    $$PWD/Process.h \
    $$PWD/Process_p.h

macx {
    SOURCES += \
        $$PWD/Process_mac.cc
}
