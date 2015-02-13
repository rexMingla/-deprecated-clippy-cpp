/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef CLIPBOARDITEM_H
#define CLIPBOARDITEM_H

#include "Headers.h"

#include "src/common/Optional.h"

#include <QList>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QByteArray>

class QMimeData;

/**
 * @brief This is a poor mans wrapper around QMimeData.
 *
 *        The data_ map is used interally rather than a QMimeData object as there were issues with QMimeData
 *        internals going out of scope and causing null pointers when used at a later time.
 */
class ClipboardItem : public QObject
{
  Q_OBJECT
private:
  QMap<QString, QByteArray> formats_; // represents QMimeData's internal format object.

public:
  ClipboardItem(const ClipboardItem& other);
  ClipboardItem(const QMimeData* mimeData = 0, QObject* parent = 0);
  ClipboardItem& operator=(const ClipboardItem& other);
  ~ClipboardItem();

  QMimeData* mimeData() const;
  const QString displayText() const;
  bool operator==(const ClipboardItem& item) const;
  bool operator!=(const ClipboardItem& item) const;

  QByteArray serialize() const;
  static Optional<ClipboardItem> deserialize(QByteArray& data);
};

Q_DECLARE_METATYPE(ClipboardItemPtr)

QDataStream& operator<<(QDataStream & istream, const ClipboardItem& item);
QDataStream& operator>>(QDataStream& ostream, ClipboardItem& item);

#endif // CLIPBOARDITEM_H
