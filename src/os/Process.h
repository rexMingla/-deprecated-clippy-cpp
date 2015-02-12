/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef PROCESS_H
#define PROCESS_H

class QKeySequence;

class ProcessPrivate;

class Process
{
private:
  ProcessPrivate* pimpl_;

public:
  Process();
  ~Process();

  void setAsFocusedWindow();
  void sendKeys(const QKeySequence& keySequence);
};

#endif // PROCESS_H
