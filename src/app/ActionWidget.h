/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include "src/clipboard/Headers.h"

#include <QWidget>

class ClipboardItem;
class ClipboardManager;
class QAction;
class QMenu;

/**
 * @brief Displays menu of all possible actions. This same widget is used by the SystemTray and also displays
 * parentless when the launch shortcut is envoked (see ActionExecutor).
 */
class ActionWidget : public QWidget
{
  Q_OBJECT
private:
  ClipboardManager* clipboardManager_;
  QMenu* menu_;
  QAction* quitAction_;
  QAction* clearHistoryAction_;
  QAction* showSettingsAction_;
  int numItemsPerGroup_;
  int numFreeItems_;

public:
  explicit ActionWidget(ClipboardManager* clipboardManager, QWidget* parent = 0);
  ~ActionWidget();

  QMenu* getMenu();

  void setNumItemsPerGroup(int numItemsPerGroup);
  void setNumFreeItems(int numFreeItems);
  bool hasClipboardAction(QAction* action);

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
