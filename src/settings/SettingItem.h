/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTINGITEM_H
#define SETTINGITEM_H

#include <QObject>
#include <QString>
#include <QVariant>

class QSettings;
class SettingMetadata;

/**
 * @brief Represents Key-value pair that is stored in QSettings class.
 */
class SettingItem : public QObject
{
  Q_OBJECT
  friend class SettingItemBuilder;

private:
  QSettings* settings_;
  const SettingMetadata* metadata_;
  const QString key_;
  const QString displayName_;
  bool isHidden_;

public:
  SettingItem(QSettings* settings,
      const SettingMetadata* metadata,
      const QString& key);
  virtual ~SettingItem();

  const QString& key() const;
  const QString& displayName() const;
  bool isHidden() const;
  QVariant value() const;
  bool setValue(const QVariant& value);
  bool setValue(const QVariant& value, QString& error);
  const SettingMetadata& metadata() const;

signals:
  void settingsChangedSignal(const QVariant& value);
};

#endif // SETTINGITEM_H
