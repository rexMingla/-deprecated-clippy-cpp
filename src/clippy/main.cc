#include "ActionWidget.h"
#include "ClipboardManager.h"
#include "ConfigWidget.h"
#include "SystemTray.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(true);

    ActionWidget* actionWidget = new ActionWidget();
    //QObject::connect(actionWidget, setImage(const QImage&);
    //QObject::connect(actionWidget, setMimeData(QMimeData* src);
    //QObject::connect(actionWidget, setPixmap(const QPixmap& pixmap);
    //QObject::connect(actionWidget, setText(c

    SystemTray* systemTray = new SystemTray(actionWidget);
    ConfigWidget* configWidget = new ConfigWidget(systemTray);
    configWidget->show();
    QObject::connect(systemTray, SIGNAL(showSettings()), configWidget, SLOT(show()));

    ClipboardManager* clipboardManager = new ClipboardManager(systemTray);
    configWidget->show();


    return a.exec();
}
