#include "ClipboardItem.h"

#include "vendor/qxt/qxtlogger.h"

#include <QMimeData>
#include <QTextDocument>

namespace {
  // breaks the pre-processor, see:
  // http://stackoverflow.com/questions/14216510/qt-foreach-with-templates-with-multiple-parameters
  typedef QPair<QString, QByteArray> SerializedType;
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
    data_[format] = mimeData->data(format);
  }
}

ClipboardItem& ClipboardItem::operator=(const ClipboardItem& other) {
  data_ = other.data_;
  return *this;
}

ClipboardItem::~ClipboardItem() {
}

QMimeData* ClipboardItem::mimeData() const {
  QMimeData* ret = new QMimeData();
  foreach (const QString& key, data_.keys()) {
    ret->setData(key, data_[key]);
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
  return data_ == other.data_;
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
    qxtLog->debug("unable to deserialize data. ex=", ex.what());
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
