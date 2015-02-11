#include "Settings.h"

#include "src/global/Optional.h"
#include "SettingItem.h"
#include "ChoiceValidator.h"
#include "NoopValidator.h"
#include "RangeSettingValidator.h"

#include "vendor/qxt/qxtlogger.h"

#include <QKeySequence>
#include <QSettings>

Settings::Settings(const QString& filename, QObject* parent)
  : QObject(parent)
{
  qxtLog->info("loading settings file=", filename);
  settings_ = new QSettings(filename, QSettings::NativeFormat);
  numFreeItems_ = new SettingItem(settings_, "num_free_items", QVariant(0),
      SettingItem::INT, new RangeSettingValidator(Optional<int>::of(0), Optional<int>::of(10)));
  numItemsPerGroup_ = new SettingItem(settings_, "num_items_per_group", QVariant(10),
      SettingItem::INT, new RangeSettingValidator(Optional<int>::of(5), Optional<int>::of(100)));
  maxNumItems_ = new SettingItem(settings_, "max_num_items", QVariant(30),
      SettingItem::INT, new RangeSettingValidator(Optional<int>::of(10), Optional<int>::of(1000)));
  persistBetweenSessions_ = new SettingItem(settings_, "persist_between_sessions", QVariant(true),
      SettingItem::BOOL, new NoopSettingValidator());
  history_ = new SettingItem(settings_, "history", QVariant(QList<QVariant>()),
      SettingItem::LIST, new NoopSettingValidator());
  QKeySequence defaultLaunchKey = QKeySequence("Ctrl+Shift+V");
  launchShortcutKeySequence_ = new SettingItem(settings_, "launch_shortcut_key_sequence",
      defaultLaunchKey, SettingItem::KEY_SEQUENCE, new NoopSettingValidator());

  addItem(numFreeItems_);
  addItem(numItemsPerGroup_);
  addItem(maxNumItems_);
  addItem(history_); // TODO: add property to keep this hidden from modification
  addItem(persistBetweenSessions_);
  addItem(launchShortcutKeySequence_);

#ifdef Q_WS_MAC
  QList<QVariant> timeoutValues;
  timeoutValues << QVariant(0.25) << QVariant(0.5) << QVariant(0.75) << QVariant(1.0);
  clipboardRefreshTimeoutSecs_ =  new SettingItem(settings_,
      "clipboard_refresh_timeout_ms", QVariant(0.5),
      SettingItem::FLOAT, new ChoiceSettingValidator(timeoutValues));
  addItem(clipboardRefreshTimeoutSecs_);
#endif
}

Settings::~Settings() {
}

SettingItem* Settings::numFreeItems() {
  return numFreeItems_;
}

SettingItem* Settings::numItemsPerGroup() {
  return numItemsPerGroup_;
}

SettingItem* Settings::maxNumItems() {
  return maxNumItems_;
}

SettingItem* Settings::clipboardRefreshTimeoutSecs() {
  return clipboardRefreshTimeoutSecs_;
}

SettingItem* Settings::persistBetweenSessions() {
  return persistBetweenSessions_;
}

SettingItem* Settings::history() {
  return history_;
}

SettingItem* Settings::launchShortcutKeySequence() {
  return launchShortcutKeySequence_;
}

QList<SettingItem*>& Settings::settings() {
  return settingList_;
}

void Settings::addItem(SettingItem* item) {
  settingList_.append(item);
  connect(item, SIGNAL(settingsChangedSignal(const QVariant&)), SIGNAL(settingsChangedSignal()));
}

void Settings::loadConfig() {
  foreach (SettingItem* item, settings()) {
    item->setValue(item->value()); // TODO: this is a hack. do this better!
  }
}

void Settings::saveConfig() {
  settings_->sync();
}
