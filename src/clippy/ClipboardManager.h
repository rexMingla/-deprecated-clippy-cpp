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

class ClipboardManager : public QObject
{
    Q_OBJECT
public:
    static const int MIN_ITEMS = 1;
    static const int MAX_ITEMS = 1000;

private:
    QList<ClipboardItem::Ptr> items_;
    QClipboard* clipboard_;
    int maxSize_;

public:
    explicit ClipboardManager(QObject* parent = 0);
    ~ClipboardManager();

    void setMaxItems(int maxSize);
    const QList<ClipboardItem::Ptr>& getItems();

private:
    void cleanupItems();

public slots:
    void setImage(const QImage& image);
    void setMimeData(QMimeData* src);
    void setPixmap(const QPixmap& pixmap);
    void setText(const QString& text);

private slots:
    void onClipboardChanged();
};

#endif // CLIPBOARDMANAGER_H
