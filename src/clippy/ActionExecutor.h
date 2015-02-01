#ifndef ACTIONEXECUTOR_H
#define ACTIONEXECUTOR_H

#include <QObject>

class ActionExecutor : public QObject
{
  Q_OBJECT
public:
  explicit ActionExecutor(QObject* parent = 0);
  ~ActionExecutor();

signals:

public slots:
};

#endif // ACTIONEXECUTOR_H
