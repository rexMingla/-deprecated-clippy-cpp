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
  bool ignoreNextValue_;

public:
  explicit ClipboardManager(Settings* settings, QObject* parent = 0);
  ~ClipboardManager();

  const QList<ClipboardItem::Ptr>& items();

private:
  void cleanupItems();
  void loadConfig();

public slots:
  void saveConfig();
  void clearItems();
  void setMimeData(ClipboardItem::Ptr data);
  void setText(const QString& text);

private slots:
  void onClipboardChanged();
  void onMaxNumItemsChanged(const QVariant& value);
};

#endif // CLIPBOARDMANAGER_H
