/* See the file "LICENSE.md" for the full license governing this code. */
#include "SettingItem.h"
#include "SettingValidator.h"

#include "src/global/Logger.h"

#include <QSettings>

namespace {
  Logger log("SettingItem");
}

SettingItem::SettingItem(QSettings* settings, const QString& key, const QVariant& defaultValue,
    SettingItem::SettingType type, const SettingValidator* validator)
  : QObject(settings),
    settings_(settings),
    key_(key),
    type_(type),
    validator_(validator),
    defaultValue_(defaultValue) {
  QVariant val = value();
  if (val.isNull() || !validator_->isValid(val)) {
    setValue(defaultValue);
  }
}

SettingItem::~SettingItem() {
  delete validator_;
}

SettingItem::SettingType SettingItem::type() const {
  return type_;
}

QVariant SettingItem::value() const {
  QVariant val = settings_->value(key_);
  log.debug("value. key=", key_, " value=", val);
  return val;
}

void SettingItem::setValue(const QVariant& value) {
  if (validator_->isValid(value)) {
    log.debug("set value. key=", key_, " value=", value);
    settings_->setValue(key_, value);
    emit settingsChangedSignal(value);
  } else {
    log.warning("Setting value ignored as it's invalid. key=", key_, " ignored value=", value);
  }
}

void SettingItem::setToDefaultValue() {
  setValue(defaultValue_);
}

const SettingValidator& SettingItem::validator() const {
  return *validator_;
}
