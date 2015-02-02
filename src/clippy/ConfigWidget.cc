#include "ConfigWidget.h"

#include "Settings.h"
#include "ui_ConfigWidget.h"

#include <QObject>

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
