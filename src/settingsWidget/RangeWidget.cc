#include "RangeWidget.h"

#include "src/settings/RangeMetadata.h"
#include "src/settings/SettingItem.h"
#include "src/settings/SettingMetadata.h"

#include <QSpinBox>
#include <QVBoxLayout>

RangeWidget::RangeWidget(SettingItem* settings, QWidget* parent)
  : SettingItemWidget(settings, parent),
    ui_(new QSpinBox(this)) {
  setupUi();
  onSettingChanged(item_->value());
}

RangeWidget::~RangeWidget() {
}

void RangeWidget::onSettingChanged(const QVariant& value) {
  ui_->setValue(value.toInt());
}

void RangeWidget::onChanged() {
  setValue(ui_->value());
}

void RangeWidget::setupUi() {
  const RangeMetadata& rangeMetadata = dynamic_cast<const RangeMetadata&>(item_->metadata());
  ui_->setRange(rangeMetadata.min().toInt(), rangeMetadata.max().toInt());
  connect(ui_, SIGNAL(valueChanged(int)), SLOT(onChanged()));

  QVBoxLayout* lo = new QVBoxLayout(this);
  lo->setContentsMargins(0, 0, 0, 0);
  lo->addWidget(ui_);
}
