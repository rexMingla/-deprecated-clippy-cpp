/* See the file "LICENSE.md" for the full license governing this code. */
#include "Settings.h"

#include "HotKeyMetadata.h"
#include "ChoiceMetadata.h"
#include "NoopMetadata.h"
#include "RangeMetadata.h"
#include "SettingsConstants.h"
#include "SettingItemBuilder.h"
#include "SettingItem.h"

#include "src/common/Logger.h"
#include "src/common/Optional.h"

#include <QKeySequence>
#include <QSettings>

#include <stdexcept>

namespace {
  Logger log("Settings");
}

Settings::Settings(const QString& filename, QObject* parent)
  : QObject(parent)
{
  log.info("loading settings file=", filename);
  qsettings_ = new QSettings(filename, QSettings::NativeFormat);
  addItem(SettingItemBuilder(new RangeMetadata(10, 0, 10))
      .withSettings(qsettings_)
      .withKey(SettingsConstants::NUM_FREE_ITEMS)
      .withDisplayName("Number of items in main menu")
      .build());

  addItem(SettingItemBuilder(new RangeMetadata(10, 5, 10))
      .withSettings(qsettings_)
      .withKey(SettingsConstants::NUM_ITEMS_PER_GROUP)
      .withDisplayName("Number of items in each group")
      .build());

  addItem(SettingItemBuilder(new RangeMetadata(30, 10, 1000))
      .withSettings(qsettings_)
      .withKey(SettingsConstants::MAX_NUM_ITEMS)
      .withDisplayName("Max number of items to keep in history")
      .build());

  addItem(SettingItemBuilder(new NoopSettingMetadata(true))
      .withSettings(qsettings_)
      .withKey(SettingsConstants::PERSIST_BETWEEN_SESSIONS)
      .withDisplayName("Preserve history between sessions")
      .build());

  addItem(SettingItemBuilder(new NoopSettingMetadata(QList<QVariant>()))
      .withSettings(qsettings_)
      .withKey(SettingsConstants::HISTORY)
      .withIsHidden(true)
      .build());

  addItem(SettingItemBuilder(new HotKeyMetadata(QKeySequence("Ctrl+Shift+V")))
      .withSettings(qsettings_)
      .withKey(SettingsConstants::LAUNCH_SHORTCUT_KEY)
      .withDisplayName("Launch menu shortcut key")
      .build());

#ifdef Q_WS_MAC
  QList<QVariant> timeoutValues;
  timeoutValues << QVariant(0.25) << QVariant(0.5) << QVariant(0.75) << QVariant(1.0);
  addItem(SettingItemBuilder(new ChoiceMetadata(QVariant(0.5), timeoutValues))
      .withSettings(qsettings_)
      .withKey(SettingsConstants::CLIPBOARD_REFRESH_TIMEOUT_SECS)
      .withDisplayName("Time interval to check clipboard has changed (secs)")
      .build());
#endif
}

Settings::~Settings() {
}

SettingItem*Settings::setting(const QString& key) {
  foreach (SettingItem* item, settings_) {
    if (item->key() == key) {
      return item;
    }
  }
  throw std::runtime_error("setting with key not found. key=" + key.toStdString());
}

QList<SettingItem*>& Settings::settings() {
  return settings_;
}

void Settings::addItem(SettingItem* item) {
  settings_.append(item);
  connect(item, SIGNAL(settingsChangedSignal(const QVariant&)), SIGNAL(settingsChangedSignal()));
}

void Settings::loadConfig() {
  foreach (SettingItem* item, settings()) {
    item->setValue(item->value()); // TODO: this is a hack. do this better!
  }
}

void Settings::saveConfig() {
  qsettings_->sync();
}
