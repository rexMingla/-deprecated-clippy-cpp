#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>

class ClipboardManager;
class QAction;
class QMenu;

class ActionWidget : public QWidget
{
  Q_OBJECT
private:
  ClipboardManager* clipboardManager_;
  QMenu* menu_;
  QAction* quitAction_;
  QAction* showSettingsAction_;

public:
  explicit ActionWidget(ClipboardManager* clipboardManager, QWidget* parent = 0);
  ~ActionWidget();

  QMenu* getMenu();

private slots:
  void rebuildMenu();

signals:
  void showSettingsSignal();
  //void performActionSignal(const Clipboar);
  //void actionSelected(QObject object);
};

#endif // ACTIONWIDGET_H
