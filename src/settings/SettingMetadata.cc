/* See the file "LICENSE.md" for the full license governing this code. */
#include "SettingMetadata.h"

SettingMetadata::SettingMetadata(Type type, const QVariant& defaultValue)
  : type_(type),
    defaultValue_(defaultValue),
    isHidden_(false) {
}

SettingMetadata::~SettingMetadata() {
}

void SettingMetadata::setDisplayName(const QString& name) {
  displayName_ = name;
}

void SettingMetadata::setIsHidden(bool isHidden) {
  isHidden_ = isHidden;
}

const QString& SettingMetadata::displayName() const {
  return displayName_;
}

bool SettingMetadata::isHidden() const {
  return isHidden_;
}

const QVariant& SettingMetadata::defaultValue() const {
  return defaultValue_;
}

SettingMetadata::Type SettingMetadata::type() const {
  return type_;
}

bool SettingMetadata::isValid(const QVariant& value) const {
  QString error;
  return isValid(value, error);
}
