#ifndef CHECKBOXWIDGET_H
#define CHECKBOXWIDGET_H

#include "SettingItemWidget.h"

class QCheckBox;

class CheckboxWidget : public SettingItemWidget
{
  Q_OBJECT
private:
  QCheckBox* ui_;

public:
  explicit CheckboxWidget(SettingItem* settings, QWidget* parent = 0);
  ~CheckboxWidget();

protected slots:
  void onSettingChanged(const QVariant& value);

private slots:
  void onChanged();

private:
  void setupUi();
};

#endif // CHECKBOXWIDGET_H
