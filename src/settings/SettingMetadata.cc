/* See the file "LICENSE.md" for the full license governing this code. */
#include "SettingMetadata.h"

SettingMetadata::SettingMetadata(const QVariant& defaultValue)
  : defaultValue_(defaultValue),
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

QVariant::Type SettingMetadata::type() const {
  return defaultValue_.type();
}
