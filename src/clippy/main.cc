#include "ActionWidget.h"
#include "ClipboardManager.h"
#include "ConfigWidget.h"
#include "SystemTray.h"

#include "vendor/qxt/qxtbasicfileloggerengine.h"
#include "vendor/qxt/qxtbasicstdloggerengine.h"
#include "vendor/qxt/qxtlogger.h"

#include <QApplication>

static void setupLogs()
{
    // thanks to http://ynonperek.com/qt-logging
    QxtBasicFileLoggerEngine* appLog  = new QxtBasicFileLoggerEngine("clippy.app.log");
    QxtBasicSTDLoggerEngine* debugLog = new QxtBasicSTDLoggerEngine();

    qxtLog->addLoggerEngine("app", appLog);
    qxtLog->addLoggerEngine("debug", debugLog);

    qxtLog->enableLogLevels("app",  QxtLogger::InfoLevel | QxtLogger::WarningLevel |
            QxtLogger::ErrorLevel | QxtLogger::CriticalLevel | QxtLogger::FatalLevel | QxtLogger::WriteLevel );
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(true);

    setupLogs();
    qxtLog->debug("App started");

    ActionWidget* actionWidget = new ActionWidget();
    //QObject::connect(actionWidget, setImage(const QImage&);
    //QObject::connect(actionWidget, setMimeData(QMimeData* src);
    //QObject::connect(actionWidget, setPixmap(const QPixmap& pixmap);
    //QObject::connect(actionWidget, setText(c

    SystemTray* systemTray = new SystemTray(actionWidget);
    ConfigWidget* configWidget = new ConfigWidget(systemTray);
    configWidget->show();
    QObject::connect(systemTray, SIGNAL(showSettings()), configWidget, SLOT(show()));

    ClipboardManager* clipboardManager = new ClipboardManager(systemTray);
    configWidget->show();
    try {
        return a.exec();
    } catch (std::exception ex) {
        qxtLog->warning("An error occured. ex=", ex.what());
    }
}
