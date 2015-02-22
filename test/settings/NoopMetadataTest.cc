/* See the file "LICENSE.md" for the full license governing this code. */
#include "src/settings/NoopMetadata.h"

#include "test/AutoTest.h"
#include "vendor/qxt/qxtlogger.h"

#include <QtTest>

/**
 * @brief Unit tests for NoopMetadata
 */
class NoopMetadataTest : public QObject
{
  Q_OBJECT
public:
 NoopMetadataTest() {
 }

private Q_SLOTS:
 void shouldReturnTrueForValidValue() {
   NoopMetadata noop("anything");
   QString error;
   QVERIFY(noop.isValid(true, error));
}
};

DECLARE_TEST(NoopMetadataTest)

#include "NoopMetadataTest.moc"
