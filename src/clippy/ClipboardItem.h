#ifndef CLIPBOARDITEM_H
#define CLIPBOARDITEM_H

#include <QMetaType>
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

    QMimeData* mimeData() const;
    const QString displayText() const;
    static QMimeData* copyMimeData(const QMimeData* from);
    static bool isMimeDataEqual(const QMimeData* left, const QMimeData* right);
};

QDataStream & operator<<(QDataStream & istream, const ClipboardItem& item);
QDataStream& operator>>(QDataStream &ostream, ClipboardItem& item);

Q_DECLARE_METATYPE(ClipboardItem::Ptr);

#endif // CLIPBOARDITEM_H
