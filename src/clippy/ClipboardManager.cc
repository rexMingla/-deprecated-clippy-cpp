#include <QImage>
#include <QMimeData>
#include <QPixmap>
#include <QString>

#include "ClipboardManager.h"



ClipboardManager::ClipboardManager(QObject* parent) : QObject(parent)
{

}

ClipboardManager::~ClipboardManager()
{

}

void ClipboardManager::setImage(const QImage&) {
}

void ClipboardManager::setMimeData(QMimeData*) {

}

void ClipboardManager::setPixmap(const QPixmap&) {

}

void ClipboardManager::setText(const QString&) {

}
