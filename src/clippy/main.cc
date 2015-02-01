#include "ActionWidget.h"
#include "ClipboardManager.h"
#include "ClipboardPoller.h"
#include "ConfigWidget.h"

#include "vendor/qxt/qxtbasicfileloggerengine.h"
#include "vendor/qxt/qxtbasicstdloggerengine.h"
#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QMessageBox>
#include <QStyle>
#include <QSystemTrayIcon>

static void setupLogs()
{
  // thanks to qxt and http://ynonperek.com/qt-logging
  QxtBasicFileLoggerEngine* appLog  = new QxtBasicFileLoggerEngine("clippy.app.log");
  QxtBasicSTDLoggerEngine* debugLog = new QxtBasicSTDLoggerEngine();

  qxtLog->addLoggerEngine("app", appLog);
  qxtLog->addLoggerEngine("debug", debugLog);

  qxtLog->enableLogLevels("app",  QxtLogger::InfoLevel | QxtLogger::WarningLevel
      | QxtLogger::ErrorLevel | QxtLogger::CriticalLevel | QxtLogger::FatalLevel
      | QxtLogger::WriteLevel );
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setQuitOnLastWindowClosed(false); // closed via ActionWidget quit action

  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    QMessageBox::critical(0, "Systray", "System tray required for application and "
        "none found. App is closing.");
    return 1;
  }

  setupLogs();
  qxtLog->info("App started");

  //qRegisterMetaType<ClipboardItem::Ptr>("ClipboardItem::Ptr");

  //QObject::connect(actionWidget, setImage(const QImage&);
  //QObject::connect(actionWidget, setMimeData(QMimeData* src);
  //QObject::connect(actionWidget, setPixmap(const QPixmap& pixmap);
  //QObject::connect(actionWidget, setText(c

  ConfigWidget* configWidget = new ConfigWidget();
  QWidget* parent = configWidget;
  ClipboardManager* clipboardManager = new ClipboardManager(parent);
#ifdef Q_WS_MAC
  // only mac requires polling to get global keyboard changes. link in ClipboardPoller
  ClipboardPoller* clipboardPoller = new ClipboardPoller(ClipboardPoller::DEFAULT_POLL_INTERVAL_MILLIS, parent);
  QObject::connect(clipboardPoller, SIGNAL(clipboardChangedSignal()), clipboardManager, SLOT(onClipboardChanged()));
#endif // Q_WS_MAC

  //ActionExecutor* actionExecutor = new ActionExecutor(parent);
  ActionWidget* actionWidget = new ActionWidget(clipboardManager, parent);
  QObject::connect(actionWidget, SIGNAL(showSettingsSignal()), configWidget, SLOT(show()));
  QSystemTrayIcon* systemTray = new QSystemTrayIcon(parent);
  systemTray->setContextMenu(actionWidget->getMenu());
  QObject::connect(actionWidget, SIGNAL(showSettingsSignal()), configWidget, SLOT(show()));
  systemTray->setIcon(configWidget->style()->standardIcon(QStyle::SP_MessageBoxInformation)); // TODO
  systemTray->show();

  try {
    int ret = a.exec();
    qxtLog->info("App stopped by user");
    return ret;
  } catch (std::exception ex) {
    // todo: show a pop up
    qxtLog->warning("An error occured. ex=", ex.what());
    return 1;
  }
}
