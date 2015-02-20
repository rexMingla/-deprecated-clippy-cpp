/* See the file "LICENSE.md" for the full license governing this code. */
#include "SettingItem.h"
#include "SettingMetadata.h"

#include "src/common/Logger.h"

#include <QSettings>

namespace {
  Logger log("SettingItem");
}

SettingItem::SettingItem(QSettings* settings,
    const SettingMetadata* metadata,
    const QString& key)
  : QObject(settings),
    settings_(settings),
    metadata_(metadata),
    key_(key) {
  QVariant val = value();
  if (val.isNull() || !metadata_->isValid(val)) {
    setValue(metadata->defaultValue());
  }
}

SettingItem::~SettingItem() {
  delete metadata_;
}

const QString& SettingItem::key() const {
  return key_;
}

QVariant SettingItem::value() const {
  QVariant val = settings_->value(key_);
  log.debug("value. key=", key_, " value=", val);
  return val;
}

void SettingItem::setValue(const QVariant& value) {
  if (metadata_->isValid(value)) {
    log.debug("set value. key=", key_, " value=", value);
    settings_->setValue(key_, value);
    emit settingsChangedSignal(value);
  } else {
    log.warning("Setting value ignored as it's invalid. key=", key_, " ignored value=", value);
  }
}

const SettingMetadata& SettingItem::metadata() const {
  return *metadata_;
}
