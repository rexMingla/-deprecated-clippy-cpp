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
    lastClipboardContent_(new QMimeData()),
    clipboard_(QApplication::clipboard()) {
  connect(timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));

  lastClipboardContent_->setParent(this);
  ClipboardItem::copyMimeData(clipboard_->mimeData(), *lastClipboardContent_);

  setClipboardRefreshTimeoutMillis(1000); // 1 sec
}

ClipboardPoller::~ClipboardPoller() {
  delete lastClipboardContent_;
}

void ClipboardPoller::onTimeout() {
  const QMimeData* newContent = clipboard_->mimeData();
  if (newContent && !ClipboardItem::isMimeDataEqual(lastClipboardContent_, newContent)) {
    ClipboardItem::copyMimeData(newContent, *lastClipboardContent_);
    qxtLog->debug("new content");
    emit clipboardChangedSignal();
  }
}

void ClipboardPoller::setClipboardRefreshTimeoutMillis(int value) {
  timer_->setInterval(value);
  timer_->start();
}
