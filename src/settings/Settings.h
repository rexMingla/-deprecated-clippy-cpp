#ifndef SETTINGS_H
#define SETTINGS_H

#include <QList>
#include <QObject>

class SettingItem;
class QSettings;
class SettingItem;

class Settings : public QObject
{
  Q_OBJECT
private:
  QSettings* settings_;
  SettingItem* numFreeItems_;
  SettingItem* numItemsPerGroup_;
  SettingItem* maxNumItems_;
  SettingItem* clipboardRefreshTimeoutSecs_;
  SettingItem* persistBetweenSessions_;
  SettingItem* history_;
  QList<SettingItem*> settingList_;

public:
  explicit Settings(const QString& filename, QObject* parent = 0);
  ~Settings();

  SettingItem* numFreeItems();
  SettingItem* numItemsPerGroup();
  SettingItem* maxNumItems();
  SettingItem* clipboardRefreshTimeoutSecs();
  SettingItem* persistBetweenSessions();
  SettingItem* history();
  QList<SettingItem*>& settings();

private:
  void addItem(SettingItem* item);

public slots:
  void sync();

signals:
  void settingsChangedSignal();
};

#endif // SETTINGS_H
