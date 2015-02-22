/* See the file "LICENSE.md" for the full license governing this code. */
#include "BoolMetadata.h"

BoolMetadata::BoolMetadata(const QVariant& defaultValue)
  : SettingMetadata(BOOL, defaultValue) {
}

BoolMetadata::~BoolMetadata() {
}

bool BoolMetadata::isValid(const QVariant& value, QString& error) const {
  // QVariant::toBool always succeeds so just return true here
  Q_UNUSED(value);
  Q_UNUSED(error)
  return true;
}

