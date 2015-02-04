#include "Settings.h"

#include "Optional.h"
#include "SettingItem.h"
#include "SettingValidator.h"

#include "vendor/qxt/qxtlogger.h"

#include <QSettings>
#include <QSharedPointer>

namespace {
  // keys for settings
  static const QString NUM_FREE_ITEMS_KEY = "num_free_items";
  static const QString NUM_ITEMS_PER_GROUP_KEY = "num_items_per_group";
  static const QString MAX_ITEMS = "num_free_history_items";
  static const QString PERSIST_BETWEEN_SESSIONS = "persist_between_sessions";
}

Settings::Settings(const QString& filename, QObject* parent)
  : QObject(parent)
{
  qxtLog->info("loading settings file=", filename);
  settings_ = new QSettings(filename, QSettings::NativeFormat);
  numFreeItems_ = new SettingItem(settings_, "num_free_items", QVariant(0),
      SettingItem::INT, new IntSettingValidator(Optional<int>::of(0), Optional<int>::of(10)));
  numItemsPerGroup_ = new SettingItem(settings_, "num_items_per_group", QVariant(10),
      SettingItem::INT, new IntSettingValidator(Optional<int>::of(5), Optional<int>::of(100)));
  maxNumItems_ = new SettingItem(settings_, "max_num_items", QVariant(30),
      SettingItem::INT, new IntSettingValidator(Optional<int>::of(10), Optional<int>::of(1000)));
  persistBetweenSessions_ = new SettingItem(settings_, "persist_between_sessions", QVariant(true),
      SettingItem::BOOL, new NoopSettingValidator());
  history_ = new SettingItem(settings_, "history", QVariant(QList<QVariant>()),
      SettingItem::LIST, new NoopSettingValidator());

  addItem(numFreeItems_);
  addItem(numItemsPerGroup_);
  addItem(maxNumItems_);
  addItem(persistBetweenSessions_);

#ifdef Q_WS_MAC
  QList<QVariant> timeoutValues;
  timeoutValues << QVariant(0.25) << QVariant(0.5) << QVariant(0.75) << QVariant(1.0);
  clipboardRefreshTimeoutMillis_ =  new SettingItem(settings_,
      "clipboard_refresh_timeout_ms", QVariant(0.5),
      SettingItem::FLOAT, new ChoiceSettingValidator(timeoutValues));
  addItem(clipboardRefreshTimeoutMillis_);
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

SettingItem* Settings::clipboardRefreshTimeoutMillis() {
  return clipboardRefreshTimeoutMillis_;
}

SettingItem* Settings::persistBetweenSessions() {
  return persistBetweenSessions_;
}

SettingItem* Settings::history() {
  return history_;
}

QList<SettingItem*>& Settings::settings() {
  return settingList_;
}

void Settings::addItem(SettingItem* item) {
  settingList_.append(item);
  connect(item, SIGNAL(settingsChangedSignal(const QVariant&)), SIGNAL(settingsChangedSignal()));
}
