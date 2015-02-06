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
  /*void shouldReturnTrueForSameMimeData() {
    QVERIFY(ClipboardItem::isMimeDataEqual(text_, text_));
  }

  void shouldReturnFalseForDifferentMimeData() {
    QCOMPARE(false, ClipboardItem::isMimeDataEqual(text_, NULL));
  }

  void shouldBeEqualWhenMimeDataIsCopied() {
    QMimeData* copy = ClipboardItem::copyMimeData(text_);
    QCOMPARE(copy->text(), QString("test"));
    QVERIFY(ClipboardItem::isMimeDataEqual(text_, copy));
  }*/

  void shouldDeserializeTextDataBackToSameObject() {
    qxtLog->warning("1.");
    ClipboardItem item(text_);
    qxtLog->warning("2.");
    QByteArray itemData = item.serialize();
    qxtLog->warning("3.");
    ClipboardItem* copy = ClipboardItem::deserialize(itemData);
    qxtLog->warning("3a.");
    copy->mimeData()->text();
    qxtLog->warning("3b.");
    qxtLog->warning("4.");
    QVERIFY(ClipboardItem::isMimeDataEqual(copy->mimeData(), text_));
  }
};

DECLARE_TEST(ClipboardItemTest)

#include "ClipboardItemTest.moc"
