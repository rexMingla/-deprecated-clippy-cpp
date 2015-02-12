/* See the file "LICENSE.md" for the full license governing this code. */
#include "ClipboardPoller.h"

#include "ClipboardItem.h"
#include "src/settings/SettingItem.h"
#include "src/settings/Settings.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QTimer>
#include <QVariant>

ClipboardPoller::ClipboardPoller(QObject* parent)
  : QObject(parent),
    timer_(new QTimer(this)),
    clipboard_(QApplication::clipboard()) {
  connect(timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));

  lastClipboardContent_ = ClipboardItemPtr(new ClipboardItem(clipboard_->mimeData()));
  setClipboardRefreshTimeoutMillis(1000); // 1 sec
}

ClipboardPoller::~ClipboardPoller() {
}

void ClipboardPoller::onTimeout() {
  ClipboardItemPtr newContent(new ClipboardItem(clipboard_->mimeData()));
  if (*newContent != *lastClipboardContent_) {
    lastClipboardContent_ = newContent;
    qxtLog->debug("new content");
    emit clipboardChangedSignal();
  }
}

void ClipboardPoller::setClipboardRefreshTimeoutMillis(int value) {
  timer_->setInterval(value);
  timer_->start();
}
