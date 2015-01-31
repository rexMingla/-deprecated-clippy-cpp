#include "ConfigWidget.h"
#include "ui_ConfigWidget.h"

ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent),
    ui_(new Ui::ConfigWidget)
{
    ui_->setupUi(this);
}

ConfigWidget::~ConfigWidget()
{
    delete ui_;
}
