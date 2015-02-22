/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTING_ITEM_WIDGET_H
#define SETTING_ITEM_WIDGET_H

#include <QWidget>

class SettingItem;
class QVariant;

/**
 * @brief Base class to allow widgets to set/get SettingItem
 */
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
  virtual void onSettingChanged(const QVariant& value) = 0;
};

#endif // SETTING_ITEM_WIDGET_H
