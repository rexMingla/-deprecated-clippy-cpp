#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QWidget>

class Ui_ConfigWidget;

class ConfigWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ConfigWidget(QWidget* parent = 0);
  ~ConfigWidget();

private:
  Ui_ConfigWidget* ui_;
};

#endif // CONFIG_WIDGET_H
