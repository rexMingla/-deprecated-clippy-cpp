SOURCES += \
    src/app/main.cc \
    src/app/ConfigWidget.cc \
    src/app/ActionWidget.cc \
    src/app/Action.cc \
    src/app/OsManager.cc \
    src/app/ActionExecutor.cc \
    $$PWD/SettingCoordinator.cc

HEADERS += \
    src/app/ConfigWidget.h \
    src/app/ActionWidget.h \
    src/app/Action.h \
    src/app/OsManager.h \
    src/app/ActionExecutor.h \
    $$PWD/SettingCoordinator.h

FORMS += \
    src/app/ConfigWidget.ui
