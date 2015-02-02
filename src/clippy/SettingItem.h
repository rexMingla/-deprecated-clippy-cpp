#ifndef SETTINGITEM_H
#define SETTINGITEM_H

#include <QObject>
#include <QString>

class QSettings;
class SettingValidator;
class QVariant;

class SettingItem : public QObject
{
  Q_OBJECT
public:
  enum SettingType {
    INT,
    BOOL,
    STRING,
    FLOAT
  };

  QSettings* settings_;
  const QString key_;
  SettingType type_;
  const SettingValidator* validator_;

public:
  SettingItem(QSettings* settings, const QString& key, const QVariant& defaultValue,
      SettingItem::SettingType type, const SettingValidator* validator);
  virtual ~SettingItem();

  SettingType type() const;
  QVariant value() const;
  void setValue(const QVariant& value);
  const SettingValidator& validator() const;

signals:
  void settingsChangedSignal(const QVariant& value);
};

#endif // SETTINGITEM_H
