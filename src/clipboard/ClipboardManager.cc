/* See the file "LICENSE.md" for the full license governing this code. */
#include "ClipboardManager.h"

#include "ClipboardItem.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QClipboard>
#include <QDataStream>
#include <QImage>
#include <QMimeData>
#include <QPixmap>
#include <QString>
#include <QTimer>

ClipboardManager::ClipboardManager(QObject* parent)
  : QObject(parent),
    clipboard_(QApplication::clipboard()),
    maxSize_(100),
    ignoreNextValue_(false) {
  connect(clipboard_, SIGNAL(dataChanged()), this, SLOT(onClipboardChanged()));
}

ClipboardManager::~ClipboardManager() {
}

void ClipboardManager::addItem(ClipboardItemPtr item) {
  item->setParent(this); // steal ownership
  items_.push_back(item);
}

const QList<ClipboardItemPtr>& ClipboardManager::items() {
  return items_;
}

void ClipboardManager::cleanupItems() {
  if (items_.size() > maxSize_) {
     // could be more efficient here as it's likely only one item
    items_ = items_.mid(0, maxSize_);
  }
}

void ClipboardManager::clearItems() {
  items_.clear();
}

void ClipboardManager::setMimeData(ClipboardItem* data) {
  qxtLog->debug("setMimeData");
  ignoreNextValue_ = true;
  clipboard_->setMimeData(data->mimeData());
}

void ClipboardManager::setText(const QString& text) {
  qxtLog->debug("setText");
  ignoreNextValue_ = true;
  clipboard_->setText(text);
}

void ClipboardManager::setMaxSize(int maxSize) {
  maxSize_ = maxSize;
  cleanupItems();
}

void ClipboardManager::onClipboardChanged() {
  if (ignoreNextValue_) {
    ignoreNextValue_ = false;
    return;
  }
  qxtLog->debug("clipboard updated");
  const QMimeData* mimeData = clipboard_->mimeData();
  items_.push_front(ClipboardItemPtr(new ClipboardItem(mimeData, this)));
  cleanupItems();
}
