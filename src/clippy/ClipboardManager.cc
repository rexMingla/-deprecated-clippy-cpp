#include <QImage>;
#include <QMimeData>;
#include <QPixmap>;
#include <QString>;

#include "ClipboardManager.h"

ClipboardManager::ClipboardManager(QObject *parent) : QObject(parent)
{

}

ClipboardManager::~ClipboardManager()
{

}

void ClipboardManager::setImage(const QImage& image) {

}

void ClipboardManager::setMimeData(QMimeData* src) {

}

void ClipboardManager::setPixmap(const QPixmap& pixmap) {

}

void ClipboardManager::setText(const QString& text) {

}
