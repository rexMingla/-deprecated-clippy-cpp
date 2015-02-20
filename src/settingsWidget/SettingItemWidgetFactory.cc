#include "SettingItemWidgetFactory.h"

#include "ChoiceWidget.h"
#include "CheckboxWidget.h"
#include "RangeWidget.h"

#include "src/settings/ChoiceMetadata.h"
#include "src/settings/HotKeyMetadata.h"
#include "src/settings/RangeMetadata.h"
#include "src/settings/SettingItem.h"

SettingItemWidgetFactory::SettingItemWidgetFactory(QWidget* parent)
  : QObject(parent),
    parent_(parent) {
}

SettingItemWidgetFactory::~SettingItemWidgetFactory() {
}

SettingItemWidget* SettingItemWidgetFactory::createSettingsWidget(SettingItem* item) const {
  const SettingMetadata& metadata = item->metadata();
  QVariant::Type type = metadata.type();
  if (type == QVariant::Bool) {
    return new CheckboxWidget(item, parent_);
  }
  if (dynamic_cast<const RangeMetadata*>(&metadata) != 0) {
    return new RangeWidget(item, parent_);
  }
  if (dynamic_cast<const ChoiceMetadata*>(&metadata) != 0) {
    return new ChoiceWidget(item, parent_);
  }
  if (dynamic_cast<const HotKeyMetadata*>(&metadata) != 0) {
    //
  }
  return 0;
}

