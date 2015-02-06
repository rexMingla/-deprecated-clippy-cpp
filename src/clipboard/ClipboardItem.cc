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
  : QObject(),
    mimeData_(new QMimeData()) {
  mimeData_->setParent(this);
  copyMimeData(other.mimeData(), *mimeData_);
}

ClipboardItem::ClipboardItem(const QMimeData* mimeData, QObject* parent)
  : QObject(parent),
    mimeData_(new QMimeData()) {
  mimeData_->setParent(this);
  copyMimeData(mimeData, *mimeData_);
}

ClipboardItem& ClipboardItem::operator=(const ClipboardItem& other) {
  mimeData_->clear();
  copyMimeData(other.mimeData(), *mimeData_);
  return *this;
}

ClipboardItem::~ClipboardItem() {
  delete mimeData_;
}

QMimeData* ClipboardItem::mimeData() const {
  return mimeData_;
}

const QString ClipboardItem::displayText() const {
  QString ret;
  if (mimeData_->hasImage()) {
    return "<image>";
     //setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
   } else if (mimeData_->hasHtml()) {
     QTextDocument doc;
     doc.setHtml(mimeData_->html());
     ret = doc.toPlainText();
     //setTextFormat(Qt::RichText);
   } else if (mimeData_->hasText()) {
     ret = mimeData_->text();
     //setTextFormat(Qt::PlainText);
   } else {
     //setText(tr("Cannot display data"));
   }
  return ret;
}

// see http://stackoverflow.com/questions/13762140/proper-way-to-copy-a-qmimedata-object
void ClipboardItem::copyMimeData(const QMimeData* from, QMimeData& to) {
  if (!from) {
    qxtLog->debug("copyMimeData: null input");
    return ;
  }
  foreach (QString format, from->formats()) {
    // Retrieving data
    QByteArray data = from->data(format);
    // Checking for custom MIME types
    if (format.startsWith("application/x-qt")) {
      // Retrieving true format name
      int indexBegin = format.indexOf('"') + 1;
      int indexEnd = format.indexOf('"', indexBegin);
      format = format.mid(indexBegin, indexEnd - indexBegin);
    }
    qxtLog->debug("copyMimeData: format=", format, "data=", data);
    to.setData(format, data);
  }
}

bool ClipboardItem::isMimeDataEqual(const QMimeData* left, const QMimeData* right) {
  if (left == NULL && right == NULL) {
    qxtLog->debug("isMimeDataEqual: both null");
    return true;
  }
  if (left == NULL || right == NULL) {
    qxtLog->debug("isMimeDataEqual: one of the values was null");
    return false;
  }
  QStringList leftFormats = left->formats();
  QStringList rightFormats = right->formats();
  if (leftFormats.size() != rightFormats.size()) {
    qxtLog->debug("isMimeDataEqual: number of formats do not match. left=",
        leftFormats.size(), " right=", rightFormats.size());
    return false;
  }
  foreach (const QString& leftFormat, leftFormats) {
    if (!right->hasFormat(leftFormat)) {
      qxtLog->debug("isMimeDataEqual: right does not have format. format=", leftFormat);
      return false;
    }
    if (left->data(leftFormat) != right->data(leftFormat)) {
      qxtLog->debug("isMimeDataEqual: data mismatch for format. format=", leftFormat,
          " left=", left->data(leftFormat), "right=", right->data(leftFormat));
      return false;
    }
  }
  return true;
}

QByteArray ClipboardItem::serialize() const {
  QByteArray serializer;
  QDataStream stream(&serializer, QIODevice::WriteOnly);
  stream << *this;
  return serializer;
}

ClipboardItem* ClipboardItem::deserialize(QByteArray& data) {
  ClipboardItem* item = new ClipboardItem();
  QDataStream stream(&data, QIODevice::ReadOnly);
  stream >> *item;
  return item;
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
