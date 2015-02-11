#ifndef ACTIONEXECUTOR_H
#define ACTIONEXECUTOR_H

#include <QObject>

class ActionWidget;
class OsManager;
class QxtGlobalShortcut;

class ActionExecutor : public QObject
{
  Q_OBJECT
private:
  OsManager* osManager_;
  ActionWidget* actionWidget_;
  QxtGlobalShortcut* launchMenuShortcut_;

public:
  explicit ActionExecutor(OsManager* osManager, ActionWidget* actionWidget, QObject* parent = 0);
  ~ActionExecutor();

  QxtGlobalShortcut* launchMenuShortcut();

public slots:
  void onLaunchMenuTriggered();
};

#endif // ACTIONEXECUTOR_H
