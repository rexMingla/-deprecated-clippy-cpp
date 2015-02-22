#include "SettingItemWidgetFactory.h"

#include "ChoiceWidget.h"
#include "CheckboxWidget.h"
#include "HotKeyWidget.h"
#include "RangeWidget.h"

#include "src/settings/SettingMetadata.h"
#include "src/settings/SettingItem.h"

SettingItemWidgetFactory::SettingItemWidgetFactory(QWidget* parent)
  : QObject(parent),
    parent_(parent) {
}

SettingItemWidgetFactory::~SettingItemWidgetFactory() {
}

SettingItemWidget* SettingItemWidgetFactory::createSettingsWidget(SettingItem* item) const {
  const SettingMetadata& metadata = item->metadata();
  if (metadata.isHidden()) {
    return 0;
  }
  switch (metadata.type()) {
    case SettingMetadata::BOOL:
      return new CheckboxWidget(item, parent_);
      break;
    case SettingMetadata::RANGE:
      return new RangeWidget(item, parent_);
      break;
    case SettingMetadata::CHOICE:
      return new ChoiceWidget(item, parent_);
      break;
    case SettingMetadata::HOT_KEY:
      return new HotKeyWidget(item, parent_);
    default:
      return 0;
  }
}

