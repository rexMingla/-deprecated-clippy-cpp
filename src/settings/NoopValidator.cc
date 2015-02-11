#include "NoopValidator.h"

NoopSettingValidator::NoopSettingValidator()
  : SettingValidator() {
}

NoopSettingValidator::~NoopSettingValidator() {
}

bool NoopSettingValidator::isValid(const QVariant&) const {
  return true;
}

