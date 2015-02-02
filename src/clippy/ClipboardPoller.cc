#include "ClipboardPoller.h"

#include "ClipboardItem.h"
#include "SettingItem.h"
#include "Settings.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QTimer>
#include <QVariant>

ClipboardPoller::ClipboardPoller(Settings* settings, QObject *parent)
  : QObject(parent),
    timer_(new QTimer(this)),
    lastClipboardContent_(NULL),
    clipboard_(QApplication::clipboard()),
    isFirstTime_(true) {
  connect(timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
  connect(&settings->clipboardRefreshTimeoutMillis(), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onTimeoutSettingsChanged(const QVariant&)));
  onTimeoutSettingsChanged(settings->clipboardRefreshTimeoutMillis().value().toInt());
  timer_->start();
}

ClipboardPoller::~ClipboardPoller() {
  delete lastClipboardContent_;
}

void ClipboardPoller::onTimeout() {
  const QMimeData* newContent = clipboard_->mimeData();
  if (newContent != NULL && !ClipboardItem::isMimeDataEqual(lastClipboardContent_, newContent)) {
    delete lastClipboardContent_;
    lastClipboardContent_ = ClipboardItem::copyMimeData(newContent);
    if (!isFirstTime_ && newContent != NULL) {
      qxtLog->debug("new content");
      emit clipboardChangedSignal();
      isFirstTime_ = false;
    }
  }
}

void ClipboardPoller::onTimeoutSettingsChanged(const QVariant& timeoutMillis) {
  timer_->setInterval(1000 * timeoutMillis.toFloat());
  timer_->start();
}

