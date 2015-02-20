#ifndef CHOICEWIDGET_H
#define CHOICEWIDGET_H

#include "SettingItemWidget.h"

class QComboBox;

class ChoiceWidget : public SettingItemWidget
{
  Q_OBJECT
private:
  QComboBox* ui_;

public:
  explicit ChoiceWidget(SettingItem* settings, QWidget* parent = 0);
  ~ChoiceWidget();

protected slots:
  void onSettingChanged(const QVariant& value);

private slots:
  void onChanged();

private:
  void setupUi();
};

#endif // CHOICEWIDGET_H
