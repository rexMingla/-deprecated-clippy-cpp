#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QWidget>

class ActionWidget;
class QObject;

class SystemTray : public QWidget
{
    Q_OBJECT
public:
    explicit SystemTray(ActionWidget* actionWidget, QWidget* parent = 0);
    ~SystemTray();

signals:
    void showSettings();
public slots:

private:
    ActionWidget* actionWidget_;
};

#endif // SYSTEMTRAY_H
