#include "AutoTest.h"

#include "vendor/qxt/qxtbasicstdloggerengine.h"
#include "vendor/qxt/qxtlogger.h"

#include <QDebug>

// Or supply your own main function
int main(int argc, char *argv[]) {
  QxtBasicSTDLoggerEngine* debugLog = new QxtBasicSTDLoggerEngine();
  qxtLog->addLoggerEngine("debug", debugLog);

  int failures = AutoTest::run(argc, argv);
  if (failures == 0) {
    qxtLog->info("ALL TESTS PASSED");
  } else {
    qxtLog->error(failures, " TESTS FAILED!");
  }
  return failures;
}
