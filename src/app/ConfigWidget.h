/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QWidget>

class Settings;
class Ui_ConfigWidget;

/**
 * @brief Displays application configuration.
 *
 *        TODO: not yet implemented.
 */
class ConfigWidget : public QWidget
{
  Q_OBJECT
private:
  Settings* settings_;
  Ui_ConfigWidget* ui_;

public:
  explicit ConfigWidget(Settings* settings, QWidget* parent = 0);
  ~ConfigWidget();
};

#endif // CONFIG_WIDGET_H
