#include "ClipboardManager.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QImage>
#include <QMimeData>
#include <QPixmap>
#include <QString>
#include <QClipboard>
#include <QStack>

ClipboardManager::ClipboardManager(QObject* parent) :
    QObject(parent), clipboard_(QApplication::clipboard()), maxSize_(MAX_ITEMS)
{
    connect(clipboard_, SIGNAL(dataChanged()), this, SLOT(onClipboardChanged()));
}

ClipboardManager::~ClipboardManager()
{

}

void ClipboardManager::setMaxItems(int maxSize) {
    if (MIN_ITEMS < maxSize || maxSize > MAX_ITEMS) {
        qxtLog->warning("Value ignore as not within bounds. value=", maxSize,
                ". acceptable range between ", MIN_ITEMS, " and ", MAX_ITEMS);
    }
    maxSize_ = maxSize;
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

void ClipboardManager::setMimeData(ClipboardItem::Ptr data) {
  qxtLog->debug("setMimeData");
  clipboard_->setMimeData(data->mimeData());
}

void ClipboardManager::setText(const QString& text) {
  clipboard_->setText(text, QClipboard::Clipboard);
}

void ClipboardManager::onClipboardChanged() {
  qxtLog->debug("clipboard updated");

  // example usage from http://qt-project.org/doc/qt-4.8/qclipboard.html
  const QMimeData* mimeData = clipboard_->mimeData();


  /*if (mimeData->hasImage()) {
      setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
  } else if (mimeData->hasHtml()) {
      setText(mimeData->html());
      setTextFormat(Qt::RichText);
  } else if (mimeData->hasText()) {
      setText(mimeData->text());
      setTextFormat(Qt::PlainText);
  } else {
      qxtLog->warning("Cannot display clipboard data");
  }*/
  items_.push_front(ClipboardItem::Ptr(new ClipboardItem(mimeData)));
}

const QList<ClipboardItem::Ptr>& ClipboardManager::items() {
    return items_;
}
