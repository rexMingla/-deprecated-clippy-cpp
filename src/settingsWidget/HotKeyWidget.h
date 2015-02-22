#ifndef HOTKEYEDIT_H
#define HOTKEYEDIT_H

#include "SettingItemWidget.h"

#include <QKeySequence>
#include <QWidget>

class SettingItem;
class QEvent;
class QLineEdit;
class QPushButton;

class HotKeyWidget : public SettingItemWidget
{
  Q_OBJECT
private:
  QLineEdit* edit_;
  //QPushButton* clearButton_;
  QKeySequence keySequence_;

public:
  explicit HotKeyWidget(SettingItem* item, QWidget* parent = 0);
  ~HotKeyWidget();

protected slots:
  void onSettingChanged(const QVariant& value);

protected:
  bool eventFilter(QObject* obj, QEvent* event);

private:
  void setupUi();
  void onFocusOut();
  void onFocusIn();
  void updateEdit();
  void applyKeyPress();
};

#endif // HOTKEYEDIT_H
