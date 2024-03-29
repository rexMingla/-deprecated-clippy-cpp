/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QList>
#include <QObject>

class SettingItem;
class QSettings;
class SettingItem;

/**
 * @brief Stores collection of settings
 */
class Settings : public QObject
{
  Q_OBJECT
private:
  QSettings* qsettings_;
  QList<SettingItem*> settings_;

public:
  explicit Settings(const QString& filename, QObject* parent = 0);
  ~Settings();

  SettingItem* setting(const QString& key);
  QList<SettingItem*>& settings();

private:
  void addItem(SettingItem* item);

public slots:
  void loadConfig();
  void saveConfig();

signals:
  void settingsChangedSignal();
};

#endif // SETTINGS_H
