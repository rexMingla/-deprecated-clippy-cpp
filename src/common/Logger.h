/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef LOGGER_H
#define LOGGER_H

#include <QVariant>

class QString;
class QxtLogStream;

/**
 * @brief Wrapper around qxtLog that prepends a prefix string. Primarily used to add the class name to the log
 */
class Logger
{
private:
  QString prefix_;

public:
  Logger(const QString& prefix);
  ~Logger();

  // borrowed from QxtLog
  QxtLogStream trace();
  QxtLogStream debug();
  QxtLogStream info();
  QxtLogStream warning();
  QxtLogStream error();
  QxtLogStream critical();
  QxtLogStream fatal();
  QxtLogStream write();

  // also borrowed from QxtLog, but only allow up to 9 args (rather than 10) so that we can add the prefix
  void info(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());
  void trace(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());
  void warning(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());
  void error(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());
  void debug(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());
  void critical(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());
  void fatal(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());
  void write(const QVariant& message, const QVariant& msg1 = QVariant(),
      const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
      const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
      const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
      const QVariant& msg8 = QVariant());

private:
  QxtLogStream stream(int logLevel);
};

#endif // LOGGER_H
