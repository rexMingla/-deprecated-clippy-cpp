/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTINGCOORDINATOR_H
#define SETTINGCOORDINATOR_H

#include "src/common/Optional.h"

#include <QObject>

class ActionWidget;
class ActionExecutor;
class ClipboardManager;
class ClipboardPoller;
class Settings;

/**
 * @brief Class that connects the setting values to the intended receivers.
 *
 *        Recieving classes are notified when settings are changed via this class.
 */
class SettingCoordinator : public QObject
{
  Q_OBJECT
private:
  ActionWidget* actionWidget_;
  ClipboardManager* clipboardManager_;
  Optional<ClipboardPoller*> clipboardPoller_;
  ActionExecutor* actionExecutor_;
  Settings* settings_;

public:
  explicit SettingCoordinator(ActionWidget* actionWidget,
      ClipboardManager* clipboardManager,
      Optional<ClipboardPoller*> clipboardPoller,
      ActionExecutor* actionExecutor,
      Settings* settings,
      QObject* parent = 0);
  ~SettingCoordinator();

public slots:
  void loadConfig();
  void saveConfig();

private slots:
  void onHistoryChanged(const QVariant& value);
  void onMaxNumItemsChanged(const QVariant& value);
  void onNumItemsPerGroupChanged(const QVariant& value);
  void onNumFreeItemsChanged(const QVariant& value);
  void onClipboardRefreshTimeoutSecsChanged(const QVariant& value);
  void onLaunchShortcutKeySequenceChanged(const QVariant& value);
};

#endif // SETTINGCOORDINATOR_H
