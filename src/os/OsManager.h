/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef OSMANAGER_H
#define OSMANAGER_H

#include <QObject>

class Process;

class OsManager : public QObject
{
    Q_OBJECT
public:
  explicit OsManager(QObject* parent = 0);
  ~OsManager();

  Process focusedWindow();
};

#endif // OSMANAGER_H
