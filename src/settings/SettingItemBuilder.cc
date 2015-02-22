/* See the file "LICENSE.md" for the full license governing this code. */
#include "SettingItemBuilder.h"

#include "SettingItem.h"
#include "SettingMetadata.h"

SettingItemBuilder::SettingItemBuilder(SettingMetadata* metadata)
  : metadata_(metadata) {
}

SettingItemBuilder::~SettingItemBuilder() {
}

SettingItemBuilder& SettingItemBuilder::withSettings(QSettings* settings) {
  settings_ = settings;
  return *this;
}

SettingItemBuilder& SettingItemBuilder::withKey(const QString& key) {
  key_ = key;
  return *this;
}

SettingItemBuilder& SettingItemBuilder::withDisplayName(const QString& displayName) {
  metadata_->setDisplayName(displayName);
  return *this;
}

SettingItemBuilder& SettingItemBuilder::withIsHidden(bool isHidden) {
  metadata_->setIsHidden(isHidden);
  return *this;
}

SettingItem* SettingItemBuilder::build() {
  return new SettingItem(settings_, metadata_, key_);
}

