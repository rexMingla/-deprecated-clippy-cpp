#include "ActionWidget.h"

#include "ClipboardManager.h"
#include "SettingItem.h"
#include "Settings.h"
#include "vendor/qxt/qxtlogger.h"

#include <QAction>
#include <QApplication>
#include <QMenu>

namespace {
  static const int MENU_MAX_WIDTH = 200;

  QAction* clipboardItemToAction(int index, const ClipboardItem::Ptr item, QMenu* parent) {
    QString content = item->displayText();
    QString formattedName = QString("%1. %2").arg(index).arg(content);
    QString elidedContent = parent->fontMetrics().elidedText(formattedName, Qt::ElideRight, MENU_MAX_WIDTH);
    QAction* action = new QAction(elidedContent, parent);
    action->setToolTip(content);
    action->setData(QVariant::fromValue(item));
    return action;
  }
}

ActionWidget::ActionWidget(Settings* settings, ClipboardManager* clipboardManager, QWidget* parent)
  : QWidget(parent),
    settings_(settings),
    clipboardManager_(clipboardManager),
    menu_(new QMenu(this)),
    quitAction_(new QAction("&Quit clippy", this)),
    clearHistoryAction_(new QAction("Clear History", this)),
    showSettingsAction_(new QAction("Show Settings...", this)) {

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

  // add clipboard contents (use an action group so that we can bind to the data content that
  // we need to pass on to the ClipboardManager
  const QList<ClipboardItem::Ptr>& items = clipboardManager_->items();
  QList<ClipboardItem::Ptr>::ConstIterator it = items.begin();
  QList<ClipboardItem::Ptr>::ConstIterator end = items.end();
  if (items.size() > 0) {
    QAction* historyAction = new QAction("History", menu_);
    menu_->addAction(historyAction);
    menu_->setToolTip("");
    historyAction->setEnabled(false);
  }

  int numFreeItems = settings_->numFreeItems().value().toInt();
  int i = 0;
  for (; i < std::min(items.size(), numFreeItems); ++i, ++it) {
    menu_->addAction(clipboardItemToAction(i + 1, *it, menu_));
  }
  int numItemsPerGroup = settings_->numItemsPerGroup().value().toInt();
  QMenu* subGroupMenu = NULL;
  for (; it != end; ++i, ++it) {
    if (((i - numFreeItems) % numItemsPerGroup) == 0) {
      subGroupMenu = new QMenu(QString("%1 - %2").arg(i + 1).arg(i + numItemsPerGroup));
      menu_->addMenu(subGroupMenu);
    }
    subGroupMenu->addAction(clipboardItemToAction(i + 1, *it, menu_));
  }
  menu_->addSeparator();

  connect(menu_, SIGNAL(triggered(QAction*)), SLOT(onActionTriggered(QAction*)));

  menu_->addAction(showSettingsAction_);
  menu_->addAction(clearHistoryAction_);
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
