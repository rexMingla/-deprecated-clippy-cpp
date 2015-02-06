#ifndef CLIPBOARDPOLLER_H
#define CLIPBOARDPOLLER_H

#include <QObject>

class QClipboard;
class QMimeData;
class QTimer;
class Settings;

/**
 * @brief Class required because macx os does not provide global clipboard
 * update functionality. Details here:
 * http://stackoverflow.com/questions/5033266/can-i-receive-a-callback-whenever-an-nspasteboard-is-written-to
 */
class ClipboardPoller : public QObject
{
  Q_OBJECT
private:
  QTimer* timer_;
  QMimeData* lastClipboardContent_;
  QClipboard* clipboard_;

public:
  explicit ClipboardPoller(Settings* settings, QObject *parent = 0);
  ~ClipboardPoller();

signals:
  void clipboardChangedSignal();

private slots:
  void onTimeout();
  void onTimeoutSettingsChanged(const QVariant& timeoutMillis);
};

#endif // CLIPBOARDPOLLER_H
