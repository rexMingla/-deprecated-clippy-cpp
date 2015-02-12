#include "src/clipboard/ClipboardItem.h"

#include "test/AutoTest.h"
#include "vendor/qxt/qxtlogger.h"

#include <QDataStream>
#include <QMimeData>
#include <QString>
#include <QtTest>

class ClipboardItemTest : public QObject
{
  Q_OBJECT
private:
  ClipboardItem text_;
  ClipboardItem image_;

public:
  ClipboardItemTest()
    : text_(createTextData("test")) {
  }

private Q_SLOTS:
  void shouldReturnTrueForSameObject() {
    QVERIFY(text_ == text_);
  }

  void shouldReturnTrueForSameMimeData() {
    QVERIFY(text_ == ClipboardItem(createTextData("test")));
  }

  void shouldReturnFalseForDifferentMimeData() {
    ClipboardItem other(createTextData("test2"));
    QCOMPARE(false, text_ == other);
    QVERIFY(text_ != other);
  }

  void shouldBeEqualWhenMimeDataIsCopied() {
    ClipboardItem toBeCopied = text_;
    QVERIFY(toBeCopied == text_);
    QCOMPARE(false, toBeCopied != text_);
  }

  void shouldDeserializeTextDataBackToSameObject() {
    ClipboardItem item(text_);
    QByteArray itemData = item.serialize();
    Optional<ClipboardItem> copy = ClipboardItem::deserialize(itemData);
    QVERIFY(copy.isPresent());
    QCOMPARE(copy.get(), text_);
  }

  void shouldReturnNullOnDeserializationFailure() {
    QByteArray itemData("random string");
    Optional<ClipboardItem> copy = ClipboardItem::deserialize(itemData);
    QVERIFY(copy.isAbsent());
  }

  QMimeData* createTextData(const QString& value) {
    QMimeData* ret = new QMimeData();
    ret->setText(value);
    return ret;
  }
};

DECLARE_TEST(ClipboardItemTest)

#include "ClipboardItemTest.moc"
