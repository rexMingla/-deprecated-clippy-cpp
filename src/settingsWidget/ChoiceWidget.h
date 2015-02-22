/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef CHOICEWIDGET_H
#define CHOICEWIDGET_H

#include "SettingItemWidget.h"

class QComboBox;

/**
 * @brief This class uses a combo box to allow widget to set/get SettingItem
 */
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
