/* See the file "LICENSE.md" for the full license governing this code. */
#include "src/settings/ChoiceMetadata.h"

#include "test/AutoTest.h"
#include "vendor/qxt/qxtlogger.h"

#include <QtTest>

/**
 * @brief Unit tests for ChoiceMetadata
 */
class ChoiceMetadataTest : public QObject
{
  Q_OBJECT
private:
  QString error_;
  ChoiceMetadata choice_;

public:
  ChoiceMetadataTest() : choice_("a", QList<QVariant>() << "a" << "b" << "c" << "d") {
  }

private Q_SLOTS:
  void shouldReturnTrueForValidSelection() {
    QVERIFY(choice_.isValid("b", error_));
  }

  void shouldReturnFalseForInvalidSelection() {
    QVERIFY(!choice_.isValid("e", error_));
  }
};

DECLARE_TEST(ChoiceMetadataTest)

#include "ChoiceMetadataTest.moc"
