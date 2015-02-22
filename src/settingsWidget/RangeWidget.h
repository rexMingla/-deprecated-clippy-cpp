/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef RANGEWIDGET_H
#define RANGEWIDGET_H

#include "SettingItemWidget.h"

class QSpinBox;

class RangeWidget : public SettingItemWidget
{
  Q_OBJECT
private:
  QSpinBox* ui_;

public:
  explicit RangeWidget(SettingItem* settings, QWidget* parent = 0);
  ~RangeWidget();

protected slots:
  void onSettingChanged(const QVariant& value);

private slots:
  void onChanged();

private:
  void setupUi();
};

#endif // RANGEWIDGET_H
