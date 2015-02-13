/* See the file "LICENSE.md" for the full license governing this code. */
#include "ClipboardItem.h"

#include "src/global/Logger.h"

#include <QMimeData>
#include <QStringList>
#include <QTextDocument>

namespace {
  // breaks the pre-processor, see:
  // http://stackoverflow.com/questions/14216510/qt-foreach-with-templates-with-multiple-parameters
  typedef QPair<QString, QByteArray> SerializedType;

  Logger log("ClipboardItem");
}

ClipboardItem::ClipboardItem(const ClipboardItem& other)
  : QObject() {
  *this = other;
}

ClipboardItem::ClipboardItem(const QMimeData* mimeData, QObject* parent)
  : QObject(parent) {
  if (!mimeData) {
    return ;
  }
  foreach (const QString& format, mimeData->formats()) {
    formats_[format] = mimeData->data(format);
  }
}

ClipboardItem& ClipboardItem::operator=(const ClipboardItem& other) {
  formats_ = other.formats_;
  return *this;
}

ClipboardItem::~ClipboardItem() {
}

QMimeData* ClipboardItem::mimeData() const {
  QMimeData* ret = new QMimeData();
  foreach (const QString& key, formats_.keys()) {
    ret->setData(key, formats_[key]);
  }
  return ret;
}

const QString ClipboardItem::displayText() const {
  QString ret;
  QMimeData* md = mimeData(); // TODO: fix this. horribly inefficent
  if (md->hasImage()) {
    return "<image>";
     //setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
   } else if (md->hasHtml()) {
     QTextDocument doc;
     doc.setHtml(md->html());
     ret = doc.toPlainText();
   } else if (md->hasText()) {
     ret = md->text();
   } else {
     ret = "Cannot display data";
   }
  return ret;
}

bool ClipboardItem::operator==(const ClipboardItem& other) const {
  return formats_ == other.formats_;
}

bool ClipboardItem::operator!=(const ClipboardItem& item) const {
  return !(*this == item);
}

QByteArray ClipboardItem::serialize() const {
  QByteArray serializer;
  QDataStream stream(&serializer, QIODevice::WriteOnly);
  stream << *this;
  return serializer;
}

Optional<ClipboardItem> ClipboardItem::deserialize(QByteArray& data) {
  try {
    ClipboardItem item;
    QDataStream stream(&data, QIODevice::ReadOnly);
    stream >> item;
    return Optional<ClipboardItem>::of(item);
  } catch (std::exception& ex) {
    log.warning("unable to deserialize data. ex=", ex.what());
    return Optional<ClipboardItem>::absent();
  }
}

QDataStream& operator<<(QDataStream& istream, const ClipboardItem& item) {
  const QMimeData* data = item.mimeData();
  QList<SerializedType> outData;
  foreach (const QString& format, data->formats()) {
    QByteArray value = data->data(format);
    outData << qMakePair(format, value);
  }
  istream << outData;
  return istream;
}

QDataStream& operator>>(QDataStream& ostream, ClipboardItem& item) {
  QList<SerializedType> data;
  ostream >> data;
  QMimeData* mimeData = new QMimeData();
  foreach (const SerializedType& dataItem, data) {
    mimeData->setData(dataItem.first, dataItem.second);
  }
  item = ClipboardItem(mimeData);
  return ostream;
}
