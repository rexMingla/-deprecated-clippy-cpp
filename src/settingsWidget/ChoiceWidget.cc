#include "ChoiceWidget.h"

#include "src/settings/SettingItem.h"
#include "src/settings/ChoiceMetadata.h"

#include <QComboBox>
#include <QList>
#include <QVariant>
#include <QVBoxLayout>

#include <cassert>

ChoiceWidget::ChoiceWidget(SettingItem* settings, QWidget* parent)
  : SettingItemWidget(settings, parent),
    ui_(new QComboBox(this)) {
  setupUi();
  onSettingChanged(item_->value());
}

ChoiceWidget::~ChoiceWidget() {
}

void ChoiceWidget::onSettingChanged(const QVariant& value) {
  int index = ui_->findData(value);
  assert(index != -1 && QString("value %1 not found in list").arg(value.toString()).toStdString().c_str());
  ui_->setCurrentIndex(index);
}

void ChoiceWidget::onChanged() {
  setValue(ui_->currentText());
}

void ChoiceWidget::setupUi() {
  const ChoiceMetadata& choiceMetdata = dynamic_cast<const ChoiceMetadata&>(item_->metadata());
  foreach (const QVariant& value, choiceMetdata.choices()) {
    ui_->addItem(value.toString(), value);
  }
  connect(ui_, SIGNAL(currentIndexChanged(int)), SLOT(onChanged()));

  QVBoxLayout* lo = new QVBoxLayout(this);
  lo->setContentsMargins(0, 0, 0, 0);
  lo->addWidget(ui_);
}
