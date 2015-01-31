#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>

class QObject;

class ActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActionWidget(QWidget *parent = 0);
    ~ActionWidget();

signals:
    //void actionSelected(QObject object);

public slots:
};

#endif // ACTIONWIDGET_H
