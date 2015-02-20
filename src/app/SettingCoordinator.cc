/* See the file "LICENSE.md" for the full license governing this code. */
#include "SettingCoordinator.h"

#include "ActionExecutor.h"
#include "ActionWidget.h"
#include "src/clipboard/ClipboardItem.h"
#include "src/clipboard/ClipboardManager.h"
#include "src/clipboard/ClipboardPoller.h"
#include "src/settings/SettingItem.h"
#include "src/settings/Settings.h"
#include "src/settings/SettingsConstants.h"
#include "src/common/Logger.h"

#include "vendor/qxt/qxtglobalshortcut.h"
#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QKeySequence>

namespace {
  Logger log("SettingCoordinator");
}

SettingCoordinator::SettingCoordinator(ActionWidget* actionWidget,
    ClipboardManager* clipboardManager,
    Optional<ClipboardPoller*> clipboardPoller,
    ActionExecutor* actionExecutor,
    Settings* settings,
    QObject* parent)
  : QObject(parent),
    actionWidget_(actionWidget),
    clipboardManager_(clipboardManager),
    clipboardPoller_(clipboardPoller),
    actionExecutor_(actionExecutor),
    settings_(settings) {

  // setup action widget
  connect(settings_->setting(SettingsConstants::NUM_FREE_ITEMS), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onNumFreeItemsChanged(const QVariant&)));
  connect(settings_->setting(SettingsConstants::NUM_ITEMS_PER_GROUP), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onNumItemsPerGroupChanged(const QVariant&)));

  // setup clipboard manager
  connect(settings_->setting(SettingsConstants::MAX_NUM_ITEMS), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onMaxNumItemsChanged(const QVariant&)));
  connect(settings_->setting(SettingsConstants::HISTORY), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onHistoryChanged(const QVariant&)));

  // setup clipboard poller
  if (!clipboardPoller_.isAbsent()) {
    connect(settings->setting(SettingsConstants::CLIPBOARD_REFRESH_TIMEOUT_SECS),
        SIGNAL(settingsChangedSignal(const QVariant&)),
        SLOT(onClipboardRefreshTimeoutSecsChanged(const QVariant&)));
  }

  // setup action executor
  connect(settings->setting(SettingsConstants::LAUNCH_SHORTCUT_KEY), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onLaunchShortcutKeySequenceChanged(const QVariant&)));

  // make sure we save out our settings
  connect(qApp, SIGNAL(aboutToQuit()), SLOT(saveConfig()));
}

SettingCoordinator::~SettingCoordinator() {
}

void SettingCoordinator::saveConfig() {
  log.debug("saveConfig");
  bool persistData = settings_->setting(SettingsConstants::PERSIST_BETWEEN_SESSIONS)->value().toBool();
  if (persistData) {
    QList<QVariant> list;
    foreach (const ClipboardItemPtr& item, clipboardManager_->items()) {
      QByteArray array = item->serialize();
      list << array;
    }
    settings_->setting(SettingsConstants::HISTORY)->setValue(list);
  }
  settings_->saveConfig();
}

void SettingCoordinator::loadConfig() {
  log.debug("loadConfig");
  settings_->loadConfig();
}

void SettingCoordinator::onHistoryChanged(const QVariant& value) {
  clipboardManager_->clearItems();
  QList<QVariant> list = value.toList();
  foreach (const QVariant& variantItem, list) {
    QByteArray byteArray = variantItem.toByteArray();
    Optional<ClipboardItem> item = ClipboardItem::deserialize(byteArray);
    if (item.isPresent()) {
      clipboardManager_->addItem(ClipboardItemPtr(new ClipboardItem(item.get())));
    }
  }
}

void SettingCoordinator::onMaxNumItemsChanged(const QVariant& value) {
  clipboardManager_->setMaxSize(value.toInt());
}

void SettingCoordinator::onNumItemsPerGroupChanged(const QVariant& value) {
  actionWidget_->setNumItemsPerGroup(value.toInt());
}

void SettingCoordinator::onNumFreeItemsChanged(const QVariant& value) {
  actionWidget_->setNumFreeItems(value.toInt());
}

void SettingCoordinator::onClipboardRefreshTimeoutSecsChanged(const QVariant& value) {
  clipboardPoller_.get()->setClipboardRefreshTimeoutMillis(1000 * value.toFloat());
}

void SettingCoordinator::onLaunchShortcutKeySequenceChanged(const QVariant& value) {
  QxtGlobalShortcut* shortcut = actionExecutor_->launchMenuShortcut();
  shortcut->setEnabled(); // TODO
  QKeySequence ks = value.value<QKeySequence>();
  shortcut->setShortcut(ks);
}
