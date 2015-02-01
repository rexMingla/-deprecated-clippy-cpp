#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>

class ClipboardManager;
class QAction;
class QMenu;
class ClipboardItem;

class ActionWidget : public QWidget
{
  Q_OBJECT
private:
  ClipboardManager* clipboardManager_;
  QMenu* menu_;
  QAction* quitAction_;
  QAction* clearHistoryAction_;
  QAction* showSettingsAction_;

public:
  explicit ActionWidget(ClipboardManager* clipboardManager, QWidget* parent = 0);
  ~ActionWidget();

  QMenu* getMenu();

private slots:
  void rebuildMenu();
  void onActionTriggered(QAction* action);

signals:
  void showSettingsSignal();
  void performActionSignal(const ClipboardItem&);
  //void actionSelected(QObject object);
};

#endif // ACTIONWIDGET_H
