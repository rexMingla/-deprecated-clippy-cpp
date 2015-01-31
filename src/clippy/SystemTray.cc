#include "SystemTray.h"

#include "ActionWidget.h"

#include <QObject>

SystemTray::SystemTray(ActionWidget* actionWidget, QWidget* parent) :
    QWidget(parent),
    actionWidget_(actionWidget)
{
}

SystemTray::~SystemTray()
{
}

