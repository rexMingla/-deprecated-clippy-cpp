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
class Settings;

class ClipboardManager : public QObject
{
  Q_OBJECT
private:
  Settings* settings_;
  QList<ClipboardItemPtr> items_;
  QClipboard* clipboard_;
  int maxSize_;
  bool ignoreNextValue_;

public:
  explicit ClipboardManager(Settings* settings, QObject* parent = 0);
  ~ClipboardManager();

  const QList<ClipboardItemPtr>& items();

private:
  void cleanupItems();
  void loadConfig();

public slots:
  void saveConfig();
  void clearItems();
  void setMimeData(ClipboardItem* data);
  void setText(const QString& text);

private slots:
  void onClipboardChanged();
  void onMaxNumItemsChanged(const QVariant& value);
};

#endif // CLIPBOARDMANAGER_H
