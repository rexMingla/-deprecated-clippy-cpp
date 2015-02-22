/* See the file "LICENSE.md" for the full license governing this code. */
#include "src/settings/HotKeyMetadata.h"

#include "test/AutoTest.h"
#include "vendor/qxt/qxtlogger.h"

#include <QtTest>

class StandardShortcuts;

/**
 * @brief Unit tests for HotKeyMetadata
 */
class HotKeyMetadataTest : public QObject
{
 Q_OBJECT
private:
  QString error_;
  HotKeyMetadata hotKey_;

public:
 HotKeyMetadataTest() : hotKey_(QKeySequence()) {
 }

private Q_SLOTS:
  void shouldReturnTrueForDeactivatedKeySequence() {
    QVERIFY(hotKey_.isValid(QKeySequence(), error_));
  }

  void shouldReturnTrueForKeySequenceWithMetaModifierKey() {
    QVERIFY(hotKey_.isValid(QKeySequence("Meta+L"), error_));
  }

  void shouldReturnTrueForKeySequenceWithControlModifierKey() {
    QVERIFY(hotKey_.isValid(QKeySequence("Ctrl+L"), error_));
  }

  void shouldReturnTrueForKeySequenceWithAltModifierKey() {
    QVERIFY(hotKey_.isValid(QKeySequence("Alt+L"), error_));
  }

  void shouldReturnTrueForKeySequenceWithMultipleModifierKeys() {
    QVERIFY(hotKey_.isValid(QKeySequence("Ctrl+Alt+X"), error_));
  }

  void shouldReturnFalseForKeySequenceWithOnlyShiftModifierKey() {
    QVERIFY(!hotKey_.isValid(QKeySequence(QKeySequence::Paste), error_));
  }

  void shouldReturnFalseForKeySequenceWithOnlyModifierKey() {
    QVERIFY(!hotKey_.isValid(QKeySequence(Qt::ControlModifier), error_));
  }

  void shouldReturnFalseForKeySequenceWithoutModifierKey() {
    QVERIFY(!hotKey_.isValid(QKeySequence("X"), error_));
  }

  void shouldReturnFalseForKeySequenceThatMatchesSystemKey() {
    QVERIFY(!hotKey_.isValid(QKeySequence(QKeySequence::Cut), error_));
  }
};

DECLARE_TEST(HotKeyMetadataTest)

#include "HotKeyMetadataTest.moc"
