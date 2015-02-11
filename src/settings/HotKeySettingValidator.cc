#include "HotKeySettingValidator.h"

HotKeySettingValidator::HotKeySettingValidator() : SettingValidator() {
}

HotKeySettingValidator::~HotKeySettingValidator() {
}

bool HotKeySettingValidator::isValid(const QVariant &) const {
  return false; // TODO
}
