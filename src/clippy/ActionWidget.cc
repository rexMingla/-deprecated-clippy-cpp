#include "ActionWidget.h"

#include "ClipboardManager.h"
#include "vendor/qxt/qxtlogger.h"

#include <QAction>
#include <QApplication>
#include <QMenu>

ActionWidget::ActionWidget(ClipboardManager* clipboardManager, QWidget* parent)
  : QWidget(parent),
    clipboardManager_(clipboardManager),
    menu_(new QMenu(this)),
    quitAction_(new QAction("&Quit clippy", this)),
    showSettingsAction_(new QAction("Show settings", this)) {

  connect(showSettingsAction_, SIGNAL(triggered()), SIGNAL(showSettingsSignal()));
  connect(menu_, SIGNAL(aboutToShow()), SLOT(rebuildMenu()));

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
  menu_->addAction(quitAction_);
}

