#include "ClipboardItem.h"

#include "vendor/qxt/qxtlogger.h"

#include <QMimeData>

// see http://stackoverflow.com/questions/13762140/proper-way-to-copy-a-qmimedata-object
static QMimeData* copyMimeData(const QMimeData* mimeReference) {
    QMimeData* mimeCopy = new QMimeData();
    foreach(QString format, mimeReference->formats()) {
        // Retrieving data
        QByteArray data = mimeReference->data(format);
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
