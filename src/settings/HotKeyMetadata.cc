/* See the file "LICENSE.md" for the full license governing this code. */
#include "HotKeyMetadata.h"

#include <QKeySequence>

HotKeyMetadata::HotKeyMetadata(const QKeySequence& defaultValue)
  : SettingMetadata(HOT_KEY, defaultValue) {
}

HotKeyMetadata::~HotKeyMetadata() {
}

bool HotKeyMetadata::isValid(const QVariant& value, QString& error) const {
  return false; // TODO
}
