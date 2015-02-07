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

ClipboardPoller::ClipboardPoller(Settings* settings, QObject* parent)
  : QObject(parent),
    timer_(new QTimer(this)),
    lastClipboardContent_(new QMimeData()),
    clipboard_(QApplication::clipboard()) {
  connect(timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
  connect(settings->clipboardRefreshTimeoutMillis(), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onTimeoutSettingsChanged(const QVariant&)));
  onTimeoutSettingsChanged(settings->clipboardRefreshTimeoutMillis()->value().toInt());
  timer_->start();
  lastClipboardContent_->setParent(this);
  ClipboardItem::copyMimeData(clipboard_->mimeData(), *lastClipboardContent_);
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

void ClipboardPoller::onTimeoutSettingsChanged(const QVariant& timeoutMillis) {
  timer_->setInterval(1000 * timeoutMillis.toFloat());
  timer_->start();
}

