#include "SettingItem.h"
#include "SettingValidator.h"

#include "vendor/qxt/qxtlogger.h"

#include <QSettings>

SettingItem::SettingItem(QSettings* settings, const QString& key, const QVariant& defaultValue,
    SettingItem::SettingType type, const SettingValidator* validator)
  : QObject(settings),
    settings_(settings),
    key_(key),
    type_(type),
    validator_(validator) {
  setValue(defaultValue);
}

SettingItem::~SettingItem() {
  delete validator_;
}

SettingItem::SettingType SettingItem::type() const {
  return type_;
}

QVariant SettingItem::value() const {
  return settings_->value(key_);
}

void SettingItem::setValue(const QVariant& value) {
  if (validator_->isValid(value)) {
    qxtLog->debug("set value. key=", key_, " value=", value);
    settings_->setValue(key_, value);
    //emit settingsChangedSignal(value);
  } else {
    qxtLog->warning("Setting value ignored as it's invalid. key=", key_, " ignored value=", value);
  }
}

const SettingValidator& SettingItem::validator() const {
  return *validator_;
}
