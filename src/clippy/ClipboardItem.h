#ifndef CLIPBOARDITEM_H
#define CLIPBOARDITEM_H

#include <QString>
#include <QVariant>
#include <QSharedPointer>

class QMimeData;

class ClipboardItem
{
public:
    typedef QSharedPointer<ClipboardItem> Ptr;
private:
    QMimeData* mimeData_;
public:
    ClipboardItem(const QMimeData* mimeData);
    ~ClipboardItem();

    const QString value();
    static QMimeData* copyMimeData(const QMimeData* from);
    static bool isMimeDataEqual(const QMimeData* left, const QMimeData* right);
};

#endif // CLIPBOARDITEM_H
