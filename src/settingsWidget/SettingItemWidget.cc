/* See the file "LICENSE.md" for the full license governing this code. */
#include "SettingItemWidget.h"

#include "src/settings/SettingItem.h"

#include <QVariant>

SettingItemWidget::SettingItemWidget(SettingItem* item, QWidget* parent)
  : QWidget(parent),
    item_(item) {
  connect(item_, SIGNAL(settingsChangedSignal(QVariant)), SLOT(onSettingChanged(QVariant)));
}

SettingItemWidget::~SettingItemWidget() {
}

void SettingItemWidget::setValue(const QVariant& value) {
  item_->setValue(value); // TODO: handle error
}

void SettingItemWidget::onSettingChanged(const QVariant& value) {
  Q_UNUSED(value);
}
