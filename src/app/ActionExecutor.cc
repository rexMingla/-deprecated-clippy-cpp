/* See the file "LICENSE.md" for the full license governing this code. */
#include "ActionExecutor.h"

#include "ActionWidget.h"
#include "src/os/OsManager.h"
#include "src/os/Process.h"
#include "src/common/Logger.h"

#include "vendor/qxt/qxtglobalshortcut.h"
#include "vendor/qxt/qxtlogger.h"

#include <QCursor>
#include <QMenu>
#include <QPoint>

namespace {
  Logger LOGGER("ActionExecutor");
}

ActionExecutor::ActionExecutor(OsManager* osManager, ActionWidget* actionWidget, QObject *parent)
  : QObject(parent),
    osManager_(osManager),
    actionWidget_(actionWidget),
    launchMenuShortcut_(new QxtGlobalShortcut(this)) {
  connect(launchMenuShortcut_, SIGNAL(activated()), SLOT(onLaunchMenuTriggered()));
}

ActionExecutor::~ActionExecutor() {
}

QxtGlobalShortcut* ActionExecutor::launchMenuShortcut() {
  return launchMenuShortcut_;
}

void ActionExecutor::onLaunchMenuTriggered() { 
  QPoint pos = QCursor::pos();
  LOGGER.info("onLaunchMenuTriggered. cursorPos={", pos.x(), ",", pos.y(), "}");
  Process process = osManager_->focusedWindow();
  QAction* selectedAction = actionWidget_->getMenu()->exec(pos);
  process.setAsFocusedWindow();
  if (selectedAction && actionWidget_->hasClipboardAction(selectedAction)) {
    process.sendKeys(QKeySequence::Paste);
  }
}

