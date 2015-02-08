#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include "src/clipboard/Headers.h"

#include "Headers.h"

#include <QObject>
#include <QList>

class QClipboard;
class QImage;
class QMimeData;
class QPixmap;
class QString;

class ClipboardManager : public QObject
{
  Q_OBJECT
private:
  QList<ClipboardItemPtr> items_;
  QClipboard* clipboard_;
  int maxSize_;
  bool ignoreNextValue_;

public:
  explicit ClipboardManager(QObject* parent = 0);
  ~ClipboardManager();

  void addItem(ClipboardItemPtr item);
  const QList<ClipboardItemPtr>& items();

private:
  void cleanupItems();

public slots:
  void clearItems();
  void setMimeData(ClipboardItem* data);
  void setText(const QString& text);

  void setMaxSize(int maxSize);

private slots:
  void onClipboardChanged();
};

#endif // CLIPBOARDMANAGER_H
