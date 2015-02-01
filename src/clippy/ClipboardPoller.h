#ifndef CLIPBOARDPOLLER_H
#define CLIPBOARDPOLLER_H

#include <QObject>

class QClipboard;
class QMimeData;
class QTimer;

/**
 * @brief Class required because macx os does not provide global clipboard
 * update functionality. Details here:
 * http://stackoverflow.com/questions/5033266/can-i-receive-a-callback-whenever-an-nspasteboard-is-written-to
 */
class ClipboardPoller : public QObject
{
  Q_OBJECT
public:
  static const int DEFAULT_POLL_INTERVAL_MILLIS = 500;

private:
  QTimer* timer_;
  const QMimeData* lastClipboardContent_;
  QClipboard* clipboard_;

public:
  explicit ClipboardPoller(int pollIntervalMillis = DEFAULT_POLL_INTERVAL_MILLIS, QObject *parent = 0);
  ~ClipboardPoller();

signals:
  void clipboardChangedSignal();

private slots:
  void onTimeout();
};

#endif // CLIPBOARDPOLLER_H
