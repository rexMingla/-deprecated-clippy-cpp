/* See the file "LICENSE.md" for the full license governing this code. */
#include "AutoTest.h"

#include "vendor/qxt/qxtbasicstdloggerengine.h"
#include "vendor/qxt/qxtlogger.h"

#include <QDebug>

/*
 * Entry point for Qt unit tests. This 'work around' is required because Qt by default has one executable per test.
 * We want to run multiple.
 *
 * Thanks to this website for the sample framework:
 * http://qtcreator.blogspot.ca/2010/04/sample-multiple-unit-test-project.html
 */
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
