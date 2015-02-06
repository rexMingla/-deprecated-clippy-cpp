#ifndef CLIPBOARDITEM_H
#define CLIPBOARDITEM_H

#include <QMetaType>
#include <QObject>
#include <QString>
#include <QVariant>

class QMimeData;

class ClipboardItem : public QObject
{
  Q_OBJECT
private:
    QMimeData* mimeData_;
public:
    ClipboardItem(const ClipboardItem& other);
    ClipboardItem(const QMimeData* mimeData = 0, QObject* parent = 0);
    ClipboardItem& operator=(const ClipboardItem& other);
    ~ClipboardItem();

    QMimeData* mimeData() const;
    const QString displayText() const;
    static void copyMimeData(const QMimeData* from, QMimeData& to);
    static bool isMimeDataEqual(const QMimeData* left, const QMimeData* right);

    QByteArray serialize() const;
    static ClipboardItem* deserialize(QByteArray& data);
};

QDataStream & operator<<(QDataStream & istream, const ClipboardItem& item);
QDataStream& operator>>(QDataStream &ostream, ClipboardItem& item);

#endif // CLIPBOARDITEM_H
