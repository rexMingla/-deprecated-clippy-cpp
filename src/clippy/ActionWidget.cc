#include "ActionWidget.h"

#include "ClipboardManager.h"
#include "vendor/qxt/qxtlogger.h"

#include <QAction>
#include <QApplication>
#include <QMenu>

namespace {
  static const int MENU_MAX_WIDTH = 200;
}

ActionWidget::ActionWidget(ClipboardManager* clipboardManager, QWidget* parent)
  : QWidget(parent),
    clipboardManager_(clipboardManager),
    menu_(new QMenu(this)),
    quitAction_(new QAction("&Quit clippy", this)),
    clearHistoryAction_(new QAction("Clear History", this)),
    showSettingsAction_(new QAction("Show Settings", this)) {

  connect(showSettingsAction_, SIGNAL(triggered()), SIGNAL(showSettingsSignal()));
  connect(menu_, SIGNAL(aboutToShow()), SLOT(rebuildMenu()));

  connect(clearHistoryAction_, SIGNAL(triggered()), clipboardManager, SLOT(clearItems()));

  // from http://qt-project.org/doc/qt-4.8/qapplication.html#closeAllWindows
  quitAction_->setShortcuts(QKeySequence::Quit);
  connect(quitAction_, SIGNAL(triggered()), qApp, SLOT(quit()));
}

ActionWidget::~ActionWidget() {
}

QMenu* ActionWidget::getMenu() {
  return menu_;
}

void ActionWidget::rebuildMenu() {
  qxtLog->debug("rebuilding menu..");
  menu_->clear();
  menu_->addAction(showSettingsAction_);
  menu_->addAction(clearHistoryAction_);

  // add clipboard contents (use an action group so that we can bind to the data content that
  // we need to pass on to the ClipboardManager
  QMenu* historyMenu = new QMenu(menu_);
  foreach (ClipboardItem::Ptr item, clipboardManager_->items()) {
    QString content = item->displayText();
    QString elidedContent = fontMetrics().elidedText(content, Qt::ElideRight, MENU_MAX_WIDTH);
    QAction* action = new QAction(elidedContent, menu_);
    action->setToolTip(content);
    action->setData(QVariant::fromValue(item));
    historyMenu->addAction(action);
  }
  menu_->addMenu(historyMenu);
  connect(menu_, SIGNAL(triggered(QAction*)), SLOT(onActionTriggered(QAction*)));

  menu_->addSeparator();
  menu_->addAction(quitAction_);
}

void ActionWidget::onActionTriggered(QAction* action) {
  QVariant data = action->data();
  // if the item doesn't have mime data it's not an action this function cares about. ie. quit or show widget actions
  if (!data.canConvert<ClipboardItem::Ptr>()) {
    return;
  }
  ClipboardItem::Ptr item = data.value<ClipboardItem::Ptr>();
  clipboardManager_->setMimeData(item);
}

