/* See the file "LICENSE.md" for the full license governing this code. */
#include "ActionWidget.h"
#include "ActionExecutor.h"
#include "ConfigWidget.h"
#include "SettingCoordinator.h"
#include "HotKeyEdit.h"
#include "src/clipboard/ClipboardManager.h"
#include "src/clipboard/ClipboardPoller.h"
#include "src/common/Optional.h"
#include "src/common/Logger.h"
#include "src/os/OsManager.h"
#include "src/settings/Settings.h"
#include "src/settingsWidget/SettingItemWidgetFactory.h"

#include "vendor/qxt/qxtbasicfileloggerengine.h"
#include "vendor/qxt/qxtbasicstdloggerengine.h"
#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QIcon>
#include <QMessageBox>
#include <QStyle>
#include <QSystemTrayIcon>

static void setupLogs() {
  // thanks to qxt and http://ynonperek.com/qt-logging
  QxtBasicFileLoggerEngine* appLog  = new QxtBasicFileLoggerEngine("clippy.app.log");
  QxtBasicSTDLoggerEngine* debugLog = new QxtBasicSTDLoggerEngine();

  qxtLog->addLoggerEngine("app", appLog);
  qxtLog->addLoggerEngine("debug", debugLog);

  qxtLog->enableLogLevels("app",  QxtLogger::InfoLevel | QxtLogger::WarningLevel
      | QxtLogger::ErrorLevel | QxtLogger::CriticalLevel | QxtLogger::FatalLevel
      | QxtLogger::WriteLevel );
}

int main(int argc, char *argv[]) {
  QApplication* app = new QApplication(argc, argv);
  QApplication::setQuitOnLastWindowClosed(false); // closed via ActionWidget quit action

  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    QMessageBox::critical(0, "Systray", "System tray required for application and "
        "none found. App is closing.");
    return 1;
  }

  setupLogs();
  Logger log("main");
  log.info("App started");

  Settings* settings = new Settings(QApplication::applicationDirPath() + "/clippy.ini");
  SettingItemWidgetFactory* factory = new SettingItemWidgetFactory();
  ConfigWidget* configWidget = new ConfigWidget(settings, factory);
  // there is no main window so this is the master parent. it must get deleted
  QWidget* parent = configWidget;
  HotKeyEdit* hotKeyEdit = new HotKeyEdit();
  hotKeyEdit->show();
  HotKeyEdit* hotKeyEdit2 = new HotKeyEdit();
  hotKeyEdit2->show();


  ClipboardManager* clipboardManager = new ClipboardManager(parent);
  Optional<ClipboardPoller*> clipboardPoller = Optional<ClipboardPoller*>::absent();
#ifdef Q_WS_MAC
  // only mac requires polling to get global keyboard changes. link in ClipboardPoller
  clipboardPoller = Optional<ClipboardPoller*>::of(new ClipboardPoller(parent));
  QObject::connect(clipboardPoller.get(), SIGNAL(clipboardChangedSignal()), clipboardManager, SLOT(onClipboardChanged()));
#endif // Q_WS_MAC

  ActionWidget* actionWidget = new ActionWidget(clipboardManager, parent);
  QSystemTrayIcon* systemTray = new QSystemTrayIcon(parent);
  systemTray->setContextMenu(actionWidget->getMenu());
  QObject::connect(actionWidget, SIGNAL(showSettingsSignal()), configWidget, SLOT(show()));

  OsManager* osManager = new OsManager();
  ActionExecutor* actionExecutor = new ActionExecutor(osManager, actionWidget, parent);

  SettingCoordinator* settingCoordinator = new SettingCoordinator(
      actionWidget, clipboardManager, clipboardPoller, actionExecutor, settings, parent);
  settingCoordinator->loadConfig();

  // thanks to http://www.flaticon.com/free-icon/verification-of-delivery-list-clipboard-symbol_45802
  QIcon icon(":/resources/icon.png");
  systemTray->setIcon(icon);
  systemTray->show();

  try {
    int ret = app->exec();
    log.info("App stopped by user");
    return ret;
  } catch (const std::exception& ex) {
    // todo: show a pop up
    log.warning("An error occured. ex=", ex.what());
    return 1;
  }
}
