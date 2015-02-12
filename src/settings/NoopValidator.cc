/* See the file "LICENSE.md" for the full license governing this code. */
#include "NoopValidator.h"

NoopSettingValidator::NoopSettingValidator()
  : SettingValidator() {
}

NoopSettingValidator::~NoopSettingValidator() {
}

bool NoopSettingValidator::isValid(const QVariant&) const {
  return true;
}

