#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include "src/clipboard/Headers.h"

#include <QWidget>

class ClipboardItem;
class ClipboardManager;
class QAction;
class QMenu;
class Settings;

class ActionWidget : public QWidget
{
  Q_OBJECT
private:
  Settings* settings_;
  ClipboardManager* clipboardManager_;
  QMenu* menu_;
  QAction* quitAction_;
  QAction* clearHistoryAction_;
  QAction* showSettingsAction_;

public:
  explicit ActionWidget(Settings* settings, ClipboardManager* clipboardManager, QWidget* parent = 0);
  ~ActionWidget();

  QMenu* getMenu();

private:
  QAction* clipboardItemToAction(int index, const ClipboardItemPtr item, QMenu* parent);

private slots:
  void rebuildMenu();
  void onActionTriggered(QAction* action);

signals:
  void showSettingsSignal();
  void performActionSignal(const ClipboardItem&);
};

#endif // ACTIONWIDGET_H
