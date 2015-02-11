#include "OsManager.h"

#include "Process.h"

OsManager::OsManager(QObject* parent)
  : QObject(parent) {
}

OsManager::~OsManager() {
}

Process OsManager::focusedWindow() {
  return Process();
}
