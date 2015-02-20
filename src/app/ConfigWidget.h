/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QWidget>

class Settings;
class SettingItemWidgetFactory;

/**
 * @brief Displays application configuration.
 */
class ConfigWidget : public QWidget
{
  Q_OBJECT
private:
  Settings* settings_;
  SettingItemWidgetFactory* factory_;

public:
  explicit ConfigWidget(Settings* settings, SettingItemWidgetFactory* factory, QWidget* parent = 0);
  ~ConfigWidget();

private:
  void setupUi();
};

#endif // CONFIG_WIDGET_H
