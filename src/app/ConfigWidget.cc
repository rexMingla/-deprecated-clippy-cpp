/* See the file "LICENSE.md" for the full license governing this code. */
#include "ConfigWidget.h"

#include "src/common/Optional.h"
#include "src/settings/Settings.h"
#include "src/settings/SettingMetadata.h"
#include "src/settings/SettingItem.h"
#include "src/settingsWidget/SettingItemWidget.h"
#include "src/settingsWidget/SettingItemWidgetFactory.h"

#include <QGridLayout>
#include <QLabel>

ConfigWidget::ConfigWidget(Settings* settings, SettingItemWidgetFactory* factory, QWidget* parent)
  : QWidget(parent),
    settings_(settings),
    factory_(factory) {
  setupUi();
}

ConfigWidget::~ConfigWidget() {
}

void ConfigWidget::forceShow() {
  show();
  raise();
  activateWindow();
}

void ConfigWidget::setupUi() {
  QGridLayout* lo = new QGridLayout(this);
  lo->setContentsMargins(4, 4, 4, 4);
  int row = 0;
  foreach (SettingItem* item, settings_->settings()) {
    SettingItemWidget* widget = factory_->createSettingsWidget(item);
    if (!widget) {
      continue ;
    }
    const SettingMetadata& metdata = item->metadata();
    lo->addWidget(new QLabel(metdata.displayName(), this), row, 0);
    lo->addWidget(widget, row++, 1);
  }
}
