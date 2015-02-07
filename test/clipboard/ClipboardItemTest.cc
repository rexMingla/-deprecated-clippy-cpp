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
  QMimeData* text_;
  QMimeData* image_;

public:
  ClipboardItemTest()
    : text_(new QMimeData),
      image_(new QMimeData) {
    text_->setText("test");
  }

private Q_SLOTS:
  void shouldReturnTrueForSameMimeData() {
    QVERIFY(ClipboardItem::isMimeDataEqual(text_, text_));
  }

  void shouldReturnFalseForDifferentMimeData() {
    QCOMPARE(false, ClipboardItem::isMimeDataEqual(text_, NULL));
  }

  void shouldBeEqualWhenMimeDataIsCopied() {
    QMimeData toBeCopied;
    ClipboardItem::copyMimeData(text_, toBeCopied);
    QCOMPARE(toBeCopied.text(), QString("test"));
    QVERIFY(ClipboardItem::isMimeDataEqual(text_, &toBeCopied));
  }

  void shouldDeserializeTextDataBackToSameObject() {
    ClipboardItem item(text_);
    QByteArray itemData = item.serialize();
    ClipboardItem* copy = ClipboardItem::deserialize(itemData);
    QVERIFY(ClipboardItem::isMimeDataEqual(copy->mimeData(), text_));
  }
};

DECLARE_TEST(ClipboardItemTest)

#include "ClipboardItemTest.moc"
