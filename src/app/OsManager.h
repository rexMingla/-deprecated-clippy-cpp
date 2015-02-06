#ifndef OSMANAGER_H
#define OSMANAGER_H

#include <QObject>

class OsManager : public QObject
{
    Q_OBJECT
public:
    explicit OsManager(QObject* parent = 0);
    ~OsManager();

signals:

public slots:

private:

};

#endif // OSMANAGER_H
