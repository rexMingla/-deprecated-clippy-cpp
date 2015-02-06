#include "ClipboardManager.h"

#include "src/settings/SettingItem.h"
#include "src/settings/Settings.h"

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
}

void ClipboardManager::cleanupItems() {
  if (items_.size() > maxSize_) {
     // could be more efficient here as it's likely only one item
    items_ = items_.mid(0, maxSize_);
  }
}

void ClipboardManager::saveConfig() {
  qxtLog->debug("saveConfig");
  bool persistData = settings_->persistBetweenSessions()->value().toBool();
  if (persistData) {
    QList<QVariant> list;
    foreach (ClipboardItem* item, items_) {
      list << item->serialize();
    }
    settings_->history()->setValue(list);
  }
}

void ClipboardManager::loadConfig() {
  qxtLog->debug("loadConfig");
  items_.clear();
  QList<QVariant> list = settings_->history()->value().toList();
  foreach (const QVariant& variantItem, list) {
    QByteArray byteArray = variantItem.toByteArray();
    ClipboardItem* item = ClipboardItem::deserialize(byteArray);
    item->setParent(this);
    items_.push_back(item);
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

void ClipboardManager::onClipboardChanged() {
  if (ignoreNextValue_) {
    ignoreNextValue_ = false;
    return;
  }
  qxtLog->debug("clipboard updated");
  const QMimeData* mimeData = clipboard_->mimeData();
  items_.push_front(new ClipboardItem(mimeData, this));
  cleanupItems();
}

void ClipboardManager::onMaxNumItemsChanged(const QVariant& value) {
  maxSize_ = value.toInt();
  cleanupItems();
}

const QList<ClipboardItem*>& ClipboardManager::items() {
  return items_;
}
