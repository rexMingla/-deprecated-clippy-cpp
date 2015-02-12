/* See the file "LICENSE.md" for the full license governing this code. */
#include "ConfigWidget.h"
#include "ui_ConfigWidget.h"
#include "src/settings/Settings.h"

ConfigWidget::ConfigWidget(Settings* settings, QWidget* parent)
  : QWidget(parent),
    settings_(settings),
    ui_(new Ui_ConfigWidget) {
  settings_->setParent(this);
  ui_->setupUi(this);
}

ConfigWidget::~ConfigWidget() {
  delete ui_;
}
