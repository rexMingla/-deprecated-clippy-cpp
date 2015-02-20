#ifndef SETTING_ITEM_WIDGET_H
#define SETTING_ITEM_WIDGET_H

#include <QWidget>

class SettingItem;
class QVariant;

class SettingItemWidget : public QWidget
{
  Q_OBJECT
protected:
  SettingItem* item_;

public:
  explicit SettingItemWidget(SettingItem* item, QWidget* parent = 0);
  virtual ~SettingItemWidget();

protected:
  void setValue(const QVariant& value);

protected slots:
  virtual void onSettingChanged(const QVariant& value);
};

#endif // SETTING_ITEM_WIDGET_H