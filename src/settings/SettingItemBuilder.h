#ifndef SETTINGITEMBUILDER_H
#define SETTINGITEMBUILDER_H

#include <QString>

class QSettings;
class SettingItem;
class SettingMetadata;

/**
 * @brief Builder class for SettingItem
 */
class SettingItemBuilder {
private:
  QSettings* settings_;
  SettingMetadata* metadata_;
  QString key_;

public:
  SettingItemBuilder(SettingMetadata* metadata);
  ~SettingItemBuilder();

  SettingItemBuilder& withSettings(QSettings* settings);
  SettingItemBuilder& withKey(const QString& key);
  SettingItemBuilder& withDisplayName(const QString& displayName);
  SettingItemBuilder& withIsHidden(bool isHidden);

  SettingItem* build();
};

#endif // SETTINGITEMBUILDER_H
