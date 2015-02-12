/* See the file "LICENSE.md" for the full license governing this code. */
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
