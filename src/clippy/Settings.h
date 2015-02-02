#ifndef SETTINGS_H
#define SETTINGS_H

#include <QList>
#include <QObject>
#include <QSharedPointer>

class SettingItem;
class QSettings;
class SettingItem;

class Settings : public QObject
{
  Q_OBJECT
private:
  typedef QSharedPointer<SettingItem> SettingItemPtr;
  QSettings* settings_;
  SettingItemPtr numFreeItems_;
  SettingItemPtr numItemsPerGroup_;
  SettingItemPtr maxNumItems_;
  SettingItemPtr clipboardRefreshTimeoutMillis_;
  QList<SettingItemPtr> settingList_;

public:
  explicit Settings(const QString& filename, QObject* parent = 0);
  ~Settings();

  SettingItem& numFreeItems();
  SettingItem& numItemsPerGroup();
  SettingItem& maxNumItems();
  SettingItem& clipboardRefreshTimeoutMillis();
  QList<SettingItemPtr>& settings();

private:
  void addItems(SettingItemPtr item);

signals:
  void settingsChangedSignal();
};

#endif // SETTINGS_H
