/* See the file "LICENSE.md" for the full license governing this code. */
#include "src/settings/RangeMetadata.h"

#include "test/AutoTest.h"
#include "vendor/qxt/qxtlogger.h"

#include <QtTest>

/**
 * @brief Unit tests for RangeMetadata
 */
class RangeMetadataTest : public QObject
{
  Q_OBJECT
private:
  QString error_;
  RangeMetadata range_;

public:
 RangeMetadataTest() : range_(1, 3, 4) {
 }

private Q_SLOTS:
  void shouldReturnTrueWhenInRange() {
    QVERIFY(range_.isValid(3, error_));
  }

  void shouldReturnFalseWhenLowerThanRange() {
    QVERIFY(!range_.isValid(2, error_));
  }

  void shouldReturnFalseWhenHigherThanRange() {
    QVERIFY(!range_.isValid(5, error_));
  }

  void shouldReturnFalseWhenUnsupportedType() {
    QVERIFY(!range_.isValid("d", error_));
  }

};

DECLARE_TEST(RangeMetadataTest)

#include "RangeMetadataTest.moc"
