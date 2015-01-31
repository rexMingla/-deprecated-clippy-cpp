#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>

class QImage;
class QMimeData;
class QPixmap;
class QString;

class ClipboardManager : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardManager(QObject *parent = 0);
    ~ClipboardManager();

signals:

public slots:
    void setImage(const QImage& image);
    void setMimeData(QMimeData* src);
    void setPixmap(const QPixmap& pixmap);
    void setText(const QString& text);
};

#endif // CLIPBOARDMANAGER_H
