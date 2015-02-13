/* See the file "LICENSE.md" for the full license governing this code. */
#include "ActionWidget.h"

#include "src/clipboard/ClipboardItem.h"
#include "src/clipboard/ClipboardManager.h"
#include "src/clipboard/Headers.h"
#include "src/global/Logger.h"

#include <QAction>
#include <QApplication>
#include <QMenu>

namespace {
  static const int MENU_MAX_WIDTH = 200;
  Logger log("ActionWidget");
}

ActionWidget::ActionWidget(ClipboardManager* clipboardManager, QWidget* parent)
  : QWidget(parent),
    clipboardManager_(clipboardManager),
    menu_(new QMenu(this)),
    quitAction_(new QAction("&Quit clippy", this)),
    clearHistoryAction_(new QAction("Clear History", this)),
    showSettingsAction_(new QAction("Show Settings...", this)),
    numItemsPerGroup_(10),
    numFreeItems_(10) {
  connect(showSettingsAction_, SIGNAL(triggered()), SIGNAL(showSettingsSignal()));
  connect(menu_, SIGNAL(aboutToShow()), SLOT(rebuildMenu()));
  connect(clearHistoryAction_, SIGNAL(triggered()), clipboardManager, SLOT(clearItems()));

  quitAction_->setShortcuts(QKeySequence::Quit);
  connect(quitAction_, SIGNAL(triggered()), qApp, SLOT(quit()));
}

ActionWidget::~ActionWidget() {
}

QMenu* ActionWidget::getMenu() {
  return menu_;
}

void ActionWidget::setNumItemsPerGroup(int numItemsPerGroup) {
  numItemsPerGroup_ = numItemsPerGroup;
}

void ActionWidget::setNumFreeItems(int numFreeItems) {
  numFreeItems_ = numFreeItems;
}

bool ActionWidget::hasClipboardAction(QAction* action) {
  QVariant data = action->data();
  // if the item doesn't have mime data it's not an action this function cares about. ie. quit or show widget actions
  return data.canConvert<ClipboardItemPtr>();
}

QAction* ActionWidget::clipboardItemToAction(int index, const ClipboardItemPtr item, QMenu* parent) {
  QString content = item->displayText();
  QString formattedName = QString("%1. %2").arg(index).arg(content);
  QString elidedContent = parent->fontMetrics().elidedText(formattedName, Qt::ElideRight, MENU_MAX_WIDTH);
  QAction* action = new QAction(elidedContent, parent);
  action->setToolTip(content);
  action->setData(QVariant::fromValue(item));
  return action;
}

void ActionWidget::rebuildMenu() {
  log.debug("rebuilding menu..");
  menu_->clear();

  // add clipboard contents (use an action group so that we can bind to the data content that
  // we need to pass on to the ClipboardManager
  const QList<ClipboardItemPtr>& items = clipboardManager_->items();
  QList<ClipboardItemPtr>::ConstIterator it = items.begin();
  QList<ClipboardItemPtr>::ConstIterator end = items.end();
  if (items.size() > 0) {
    QAction* historyAction = new QAction("History", menu_);
    menu_->addAction(historyAction);
    menu_->setToolTip("");
    historyAction->setEnabled(false);
  }

  int i = 0;
  for (; i < std::min(items.size(), numFreeItems_); ++i, ++it) {
    menu_->addAction(clipboardItemToAction(i + 1, *it, menu_));
  }
  QMenu* subGroupMenu = NULL;
  for (; it != end; ++i, ++it) {
    if (((i - numFreeItems_) % numItemsPerGroup_) == 0) {
      subGroupMenu = new QMenu(QString("%1 - %2").arg(i + 1).arg(i + numItemsPerGroup_));
      subGroupMenu->setToolTip("");
      connect(subGroupMenu, SIGNAL(triggered(QAction*)), SLOT(onActionTriggered(QAction*)));
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
  if (hasClipboardAction(action)) {
    ClipboardItemPtr item = action->data().value<ClipboardItemPtr>();
    clipboardManager_->setMimeData(item.data());
  }
}
