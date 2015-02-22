/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTING_ITEM_WIDGET_FACTORY_H
#define SETTING_ITEM_WIDGET_FACTORY_H

#include <QObject>

class SettingItem;
class SettingItemWidget;
class QWidget;

class SettingItemWidgetFactory : public QObject
{
  Q_OBJECT
private:
  QWidget* parent_;

public:
  explicit SettingItemWidgetFactory(QWidget* parent = 0);
  ~SettingItemWidgetFactory();

  SettingItemWidget* createSettingsWidget(SettingItem* item) const;
};

#endif // SETTING_ITEM_WIDGET_FACTORY_H
