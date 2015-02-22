/* See the file "LICENSE.md" for the full license governing this code. */
#include "src/settings/BoolMetadata.h"

#include "test/AutoTest.h"
#include "vendor/qxt/qxtlogger.h"

#include <QtTest>

/**
 * @brief Unit tests for BoolMetadata
 */
class BoolMetadataTest : public QObject
{
  Q_OBJECT
private:
  QString error_;
  BoolMetadata bool_;

public:
  BoolMetadataTest() : bool_(false) {
  }

private Q_SLOTS:
  void shouldReturnTrueForValidValue() {
   QVERIFY(bool_.isValid(true, error_));
 }

 void shouldReturnTrueForAnyOtherValue() { // yep. QVariant will always cast to bool
   QVERIFY(bool_.isValid(true, error_));
 }
};

DECLARE_TEST(BoolMetadataTest)

#include "BoolMetadataTest.moc"
