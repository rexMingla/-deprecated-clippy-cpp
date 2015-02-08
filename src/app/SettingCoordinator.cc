#include "SettingCoordinator.h"

#include "ActionWidget.h"
#include "src/clipboard/ClipboardItem.h"
#include "src/clipboard/ClipboardManager.h"
#include "src/clipboard/ClipboardPoller.h"
#include "src/settings/Settings.h"
#include "src/settings/SettingItem.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>

SettingCoordinator::SettingCoordinator(ActionWidget* actionWidget,
    ClipboardManager* clipboardManager,
    Optional<ClipboardPoller*> clipboardPoller,
    Settings* settings,
    QObject *parent)
  : QObject(parent),
    actionWidget_(actionWidget),
    clipboardManager_(clipboardManager),
    clipboardPoller_(clipboardPoller),
    settings_(settings) {

  // setup action widget
  connect(settings_->numFreeItems(), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onNumFreeItemsChanged(const QVariant&)));
  connect(settings_->numItemsPerGroup(), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onNumItemsPerGroupChanged(const QVariant&)));

  // setup clipboard manager
  connect(settings_->maxNumItems(), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onMaxNumItemsChanged(const QVariant&)));

  // setup clipboard poller
  if (!clipboardPoller_.isAbsent()) {
    connect(settings->clipboardRefreshTimeoutSecs(), SLOT(settingsChangedSignal(const QVariant&)),
        SLOT(onClipboardRefreshTimeoutSecsChanged(const QVariant&)));
  }

  // make sure we save out our settings
  connect(qApp, SIGNAL(aboutToQuit()), SLOT(saveConfig()));
}

SettingCoordinator::~SettingCoordinator() {
}

void SettingCoordinator::saveConfig() {
  qxtLog->debug("saveConfig");
  bool persistData = settings_->persistBetweenSessions()->value().toBool();
  if (persistData) {
    QList<QVariant> list;
    foreach (const ClipboardItemPtr& item, clipboardManager_->items()) {
      QByteArray array = item->serialize();
      list << array;
    }
    settings_->history()->setValue(list);
  }
  settings_->sync();
}

void SettingCoordinator::loadConfig() {
  qxtLog->debug("loadConfig");
  clipboardManager_->clearItems();
  QList<QVariant> list = settings_->history()->value().toList();
  foreach (const QVariant& variantItem, list) {
    QByteArray byteArray = variantItem.toByteArray();
    ClipboardItem* item = ClipboardItem::deserialize(byteArray);
    clipboardManager_->addItem(ClipboardItemPtr(item));
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
