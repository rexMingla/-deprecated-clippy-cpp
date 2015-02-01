#include "ConfigWidget.h"

#include "ui_ConfigWidget.h"

#include <QObject>

ConfigWidget::ConfigWidget(QWidget* parent)
  : QWidget(parent),
    ui_(new Ui_ConfigWidget) {
  ui_->setupUi(this);
}

ConfigWidget::~ConfigWidget() {
  delete ui_;
}
