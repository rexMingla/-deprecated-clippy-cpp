#include "ClipboardManager.h"

#include "SettingItem.h"
#include "Settings.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QImage>
#include <QMimeData>
#include <QPixmap>
#include <QString>
#include <QClipboard>

ClipboardManager::ClipboardManager(Settings* settings, QObject* parent)
  : QObject(parent), settings_(settings),
    clipboard_(QApplication::clipboard()), maxSize_(0)
{
  connect(settings_, SIGNAL(settingsChangedSignal()), SLOT(onSettingsChanged()));
  connect(clipboard_, SIGNAL(dataChanged()), this, SLOT(onClipboardChanged()));
  onSettingsChanged();
}

ClipboardManager::~ClipboardManager() {
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
  clipboard_->setText(text);
}

void ClipboardManager::onClipboardChanged() {
  qxtLog->debug("clipboard updated");

  // example usage from http://qt-project.org/doc/qt-4.8/qclipboard.html
  const QMimeData* mimeData = clipboard_->mimeData();
  items_.push_front(ClipboardItem::Ptr(new ClipboardItem(mimeData)));
}

void ClipboardManager::onSettingsChanged() {
  int newMaxSize = settings_->maxNumItems().value().toInt();
  if (maxSize_ != newMaxSize) {
    maxSize_ = newMaxSize;
    cleanupItems();
  }
}

const QList<ClipboardItem::Ptr>& ClipboardManager::items() {
  return items_;
}
