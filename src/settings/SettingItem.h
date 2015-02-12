/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTINGITEM_H
#define SETTINGITEM_H

#include <QObject>
#include <QString>
#include <QVariant>

class QSettings;
class SettingValidator;

class SettingItem : public QObject
{
  Q_OBJECT
public:
  enum SettingType {
    INT,
    BOOL,
    STRING,
    FLOAT,
    LIST,
    KEY_SEQUENCE
  };

  QSettings* settings_;
  const QString key_;
  SettingType type_;
  const SettingValidator* validator_;
  QVariant defaultValue_;

public:
  SettingItem(QSettings* settings, const QString& key, const QVariant& defaultValue,
      SettingItem::SettingType type, const SettingValidator* validator);
  virtual ~SettingItem();

  SettingType type() const;
  QVariant value() const;
  void setValue(const QVariant& value);
  void setToDefaultValue();
  const SettingValidator& validator() const;

signals:
  void settingsChangedSignal(const QVariant& value);
};

#endif // SETTINGITEM_H
