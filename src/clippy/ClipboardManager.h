#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include "ClipboardItem.h"

#include <QObject>
#include <QList>

class QClipboard;
class QImage;
class QMimeData;
class QPixmap;
class QString;
class Settings;

class ClipboardManager : public QObject
{
  Q_OBJECT
private:
  Settings* settings_;
  QList<ClipboardItem::Ptr> items_;
  QClipboard* clipboard_;
  int maxSize_;

public:
  explicit ClipboardManager(Settings* settings, QObject* parent = 0);
  ~ClipboardManager();

  const QList<ClipboardItem::Ptr>& items();

private:
  void cleanupItems();

public slots:
  void clearItems();
  void setMimeData(ClipboardItem::Ptr data);
  void setText(const QString& text);

private slots:
  void onClipboardChanged();
  void onSettingsChanged();
};

#endif // CLIPBOARDMANAGER_H
