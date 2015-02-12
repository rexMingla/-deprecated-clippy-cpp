/* See the file "LICENSE.md" for the full license governing this code. */
#include "HotKeySettingValidator.h"

HotKeySettingValidator::HotKeySettingValidator() : SettingValidator() {
}

HotKeySettingValidator::~HotKeySettingValidator() {
}

bool HotKeySettingValidator::isValid(const QVariant &) const {
  return false; // TODO
}
