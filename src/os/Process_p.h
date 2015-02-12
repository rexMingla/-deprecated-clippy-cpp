#ifndef PROCESS_P_H
#define PROCESS_P_H
/* See the file "LICENSE.md" for the full license governing this code. */
#include <QString>

#ifdef Q_WS_MAC
class ProcessSerialNumber;
#endif // Q_WS_MAC

class QKeySequence;

/**
 * @brief Private implementation for Process class
 */
class ProcessPrivate
{
private:
  QString processName_;
#ifdef Q_WS_MAC
  ProcessSerialNumber* psn_;
#endif // Q_WS_MAC
public:
  ProcessPrivate();
  ~ProcessPrivate();

  void setAsFocusedWindow();
  void sendKeys(const QKeySequence& keySequence);
  bool isValid() const;
};

#endif // PROCESS_P_H
