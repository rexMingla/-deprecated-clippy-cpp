#include "ClipboardManager.h"

#include "SettingItem.h"
#include "Settings.h"

#include "vendor/qxt/qxtlogger.h"

#include <QApplication>
#include <QClipboard>
#include <QDataStream>
#include <QImage>
#include <QMimeData>
#include <QPixmap>
#include <QString>
#include <QTimer>

ClipboardManager::ClipboardManager(Settings* settings, QObject* parent)
  : QObject(parent),
    settings_(settings),
    clipboard_(QApplication::clipboard()),
    maxSize_(0),
    ignoreNextValue_(true) // ignore next due to start up emission
{
  connect(settings_->maxNumItems(), SIGNAL(settingsChangedSignal(const QVariant&)),
      SLOT(onMaxNumItemsChanged(const QVariant&)));
  connect(clipboard_, SIGNAL(dataChanged()), this, SLOT(onClipboardChanged()));
  onMaxNumItemsChanged(settings_->maxNumItems()->value().toInt());
  loadConfig();
}

ClipboardManager::~ClipboardManager() {
  saveConfig();
}

void ClipboardManager::cleanupItems() {
  if (items_.size() > maxSize_) {
     // could be more efficient here as it's likely only one item
    items_ = items_.mid(0, maxSize_);
  }
}

void ClipboardManager::saveConfig() {
  qxtLog->debug("saveConfig");
  if (settings_->persistBetweenSessions()->value().toBool()) {
    QList<QVariant> list;
    foreach (ClipboardItem::Ptr item, items_) {
      try {
        QDataStream s;
        s << *item.data();
        list << s;
      } catch (std::exception& ex) {
        qxtLog->warning("unable to serialize item. ex=", ex.what());
      }
      settings_->history()->setValue(list);
    }
  }
}

void ClipboardManager::loadConfig() {
  qxtLog->debug("loadConfig");
  items_.clear();
  foreach (QVariant historyItem, settings_->history()->value().toList()) {
    try {
      ClipboardItem item(NULL);
      QDataStream s;
      s << historyItem;
      s >> item;
      if (item.mimeData()) {
        items_.push_back(ClipboardItem::Ptr(new ClipboardItem(item.mimeData())));
      }
    } catch (std::exception& ex) {
      qxtLog->warning("unable to deserialize item. ex=", ex.what());
    }
  }
}

void ClipboardManager::clearItems() {
  items_.clear();
}

void ClipboardManager::setMimeData(ClipboardItem::Ptr data) {
  qxtLog->debug("setMimeData");
  ignoreNextValue_ = true;
  clipboard_->setMimeData(data->mimeData());
}

void ClipboardManager::setText(const QString& text) {
  qxtLog->debug("setText");
  ignoreNextValue_ = true;
  clipboard_->setText(text);
}

void ClipboardManager::onClipboardChanged() {
  if (ignoreNextValue_) {
    ignoreNextValue_ = false;
    return;
  }
  qxtLog->debug("clipboard updated");

  // example usage from http://qt-project.org/doc/qt-4.8/qclipboard.html
  const QMimeData* mimeData = clipboard_->mimeData();
  items_.push_front(ClipboardItem::Ptr(new ClipboardItem(mimeData)));
  cleanupItems();
}

void ClipboardManager::onMaxNumItemsChanged(const QVariant& value) {
  maxSize_ = value.toInt();
  cleanupItems();
}

const QList<ClipboardItem::Ptr>& ClipboardManager::items() {
  return items_;
}
