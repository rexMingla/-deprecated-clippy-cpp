/* See the file "LICENSE.md" for the full license governing this code. */
#include "Logger.h"

#include "vendor/qxt/qxtlogger.h"

Logger::Logger(const QString& prefix) :
  prefix_("(" + prefix + ")") {
}

Logger::~Logger() {
}

QxtLogStream Logger::info() {
  return stream(QxtLogger::InfoLevel);
}

QxtLogStream Logger::trace() {
  return stream(QxtLogger::TraceLevel);
}

QxtLogStream Logger::error() {
  return stream(QxtLogger::ErrorLevel);
}

QxtLogStream Logger::warning() {
  return stream(QxtLogger::WarningLevel);
}

QxtLogStream Logger::debug() {
  return stream(QxtLogger::DebugLevel);
}

QxtLogStream Logger::critical() {
  return stream(QxtLogger::CriticalLevel);
}

QxtLogStream Logger::fatal() {
  return stream(QxtLogger::FatalLevel);
}

QxtLogStream Logger::write() {
    return stream(QxtLogger::WriteLevel);
}

void Logger::info(const QVariant &message, const QVariant &msg1, const QVariant &msg2, const QVariant &msg3, const QVariant &msg4, const QVariant &msg5, const QVariant &msg6, const QVariant &msg7, const QVariant &msg8) {
  qxtLog->info(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

void Logger::trace(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8) {
  qxtLog->trace(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

void Logger::warning(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8) {
  qxtLog->warning(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

void Logger::error(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8) {
  qxtLog->error(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

void Logger::debug(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8) {
  qxtLog->debug(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

void Logger::write(const QVariant &message, const QVariant &msg1 , const QVariant &msg2, const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8) {
  qxtLog->write(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

void Logger::critical(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8)
{
  qxtLog->critical(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

void Logger::fatal(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8) {
  qxtLog->fatal(prefix_, message, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);
}

QxtLogStream Logger::stream(int logLevel) {
  QxtLogStream stream = qxtLog->stream(static_cast<QxtLogger::LogLevel>(logLevel));
  stream <<  prefix_;
  return stream;
}
