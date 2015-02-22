/* See the file "LICENSE.md" for the full license governing this code. */
#include "src/settings/StandardShortcuts.h"

#include "test/AutoTest.h"
#include "vendor/qxt/qxtlogger.h"

#include <QtTest>

/**
 * @brief Unit tests for StandardShortcuts
 */
class StandardShortcutsTest : public QObject
{
  Q_OBJECT
private:
  QString error_;
  StandardShortcuts shortcuts_;

public:
 StandardShortcutsTest() : shortcuts_() {
 }

private Q_SLOTS:
  void shouldReturnTrueForStandardShortcut() {
    QVERIFY(shortcuts_.isStandardShortcut(QKeySequence("Ctrl+x"), error_));
  }

  void shouldReturnFalseForNonStandardShortcut() {
    QVERIFY(!shortcuts_.isStandardShortcut(QKeySequence("x"), error_));
  }
};

DECLARE_TEST(StandardShortcutsTest)

#include "StandardShortcutsTest.moc"
