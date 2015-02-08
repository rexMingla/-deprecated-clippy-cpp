#ifndef SETTINGCOORDINATOR_H
#define SETTINGCOORDINATOR_H

#include "src/global/Optional.h"

#include <QObject>

class ActionWidget;
class ClipboardManager;
class ClipboardPoller;
class Settings;

class SettingCoordinator : public QObject
{
  Q_OBJECT
private:
  ActionWidget* actionWidget_;
  ClipboardManager* clipboardManager_;
  Optional<ClipboardPoller*> clipboardPoller_;
  Settings* settings_;

public:
  explicit SettingCoordinator(ActionWidget* actionWidget,
      ClipboardManager* clipboardManager,
      Optional<ClipboardPoller*> clipboardPoller,
      Settings* settings,
      QObject *parent = 0);
  ~SettingCoordinator();

public slots:
  void loadConfig();
  void saveConfig();

private slots:
  void onMaxNumItemsChanged(const QVariant& value);
  void onNumItemsPerGroupChanged(const QVariant& value);
  void onNumFreeItemsChanged(const QVariant& value);
  void onClipboardRefreshTimeoutSecsChanged(const QVariant& value);
};

#endif // SETTINGCOORDINATOR_H
