/* See the file "LICENSE.md" for the full license governing this code. */
#include "NoopMetadata.h"

NoopSettingMetadata::NoopSettingMetadata(const QVariant& defaultValue)
  : SettingMetadata(defaultValue) {
}

NoopSettingMetadata::~NoopSettingMetadata() {
}

bool NoopSettingMetadata::isValid(const QVariant&) const {
  return true;
}

