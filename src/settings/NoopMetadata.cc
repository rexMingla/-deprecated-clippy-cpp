#include "NoopMetadata.h"

NoopMetadata::NoopMetadata(const QVariant& defaultValue)
  : SettingMetadata(NO_OP, defaultValue) {
}

NoopMetadata::~NoopMetadata() {
}

bool NoopMetadata::isValid(const QVariant& value, QString& error) const {
  Q_UNUSED(value);
  Q_UNUSED(error);
  return true;
}

