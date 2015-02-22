/* See the file "LICENSE.md" for the full license governing this code. */
#include "CheckboxWidget.h"

#include "src/settings/SettingItem.h"

#include <QCheckBox>
#include <QVariant>
#include <QVBoxLayout>

CheckboxWidget::CheckboxWidget(SettingItem* settings, QWidget* parent)
  : SettingItemWidget(settings, parent),
    ui_(new QCheckBox(this)) {
  setupUi();
  onSettingChanged(item_->value());
}

CheckboxWidget::~CheckboxWidget() {
}

void CheckboxWidget::onSettingChanged(const QVariant& value) {
  ui_->setChecked(value.toBool());
}

void CheckboxWidget::onChanged() {
  setValue(ui_->isChecked());
}

void CheckboxWidget::setupUi() {
  connect(ui_, SIGNAL(toggled(bool)), SLOT(onChanged()));

  QVBoxLayout* lo = new QVBoxLayout(this);
  lo->setContentsMargins(0, 0, 0, 0);
  lo->addWidget(ui_);
}

