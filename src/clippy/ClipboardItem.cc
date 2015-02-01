#include "ClipboardItem.h"

#include "vendor/qxt/qxtlogger.h"

#include <QMimeData>

ClipboardItem::ClipboardItem(const QMimeData* mimeData) : mimeData_(copyMimeData(mimeData)) {
}

ClipboardItem::~ClipboardItem() {
    delete mimeData_;
}

const QString ClipboardItem::value() {
    QString ret;
    if (mimeData_->hasImage()) {
         //setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
     } else if (mimeData_->hasHtml()) {
         ret = mimeData_->html();
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
QMimeData* ClipboardItem::copyMimeData(const QMimeData* from) {
  QMimeData* mimeCopy = new QMimeData();
  foreach(QString format, from->formats()) {
    // Retrieving data
    QByteArray data = from->data(format);
    // Checking for custom MIME types
    if(format.startsWith("application/x-qt")) {
      // Retrieving true format name
      int indexBegin = format.indexOf('"') + 1;
      int indexEnd = format.indexOf('"', indexBegin);
      format = format.mid(indexBegin, indexEnd - indexBegin);
    }
    mimeCopy->setData(format, data);
  }
  return mimeCopy;
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
  foreach(QString leftFormat, leftFormats) {
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
