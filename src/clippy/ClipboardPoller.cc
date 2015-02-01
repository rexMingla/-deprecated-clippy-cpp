#include "ClipboardPoller.h"

#include "ClipboardItem.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QTimer>

ClipboardPoller::ClipboardPoller(int pollIntervalMillis, QObject *parent)
  : QObject(parent),
    timer_(new QTimer(this)),
    lastClipboardContent_(NULL),
    clipboard_(QApplication::clipboard()) {
  connect(timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
  timer_->start(pollIntervalMillis);
}

ClipboardPoller::~ClipboardPoller() {
  delete lastClipboardContent_;
}

void ClipboardPoller::onTimeout() {
  const QMimeData* newContent = clipboard_->mimeData();
  if (newContent != NULL && !ClipboardItem::isMimeDataEqual(lastClipboardContent_, newContent)) {
    delete lastClipboardContent_;
    lastClipboardContent_ = ClipboardItem::copyMimeData(newContent);
    qxtLog->debug("new content");
    if (newContent != NULL) {
      emit clipboardChangedSignal();
    }
  }
}

