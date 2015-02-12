#ifndef CLIPBOARDPOLLER_H
#define CLIPBOARDPOLLER_H

#include "Headers.h"

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
private:
  QTimer* timer_;
  ClipboardItemPtr lastClipboardContent_;
  QClipboard* clipboard_;

public:
  explicit ClipboardPoller(QObject *parent = 0);
  ~ClipboardPoller();

  void setClipboardRefreshTimeoutMillis(int value);

signals:
  void clipboardChangedSignal();

private slots:
  void onTimeout();
};

#endif // CLIPBOARDPOLLER_H
