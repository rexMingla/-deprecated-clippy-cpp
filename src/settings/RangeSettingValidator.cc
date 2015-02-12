/* See the file "LICENSE.md" for the full license governing this code. */
#include "RangeSettingValidator.h"

#include "vendor/qxt/qxtlogger.h"

#include <QVariant>

RangeSettingValidator::RangeSettingValidator(Optional<int> min, Optional<int> max)
  : SettingValidator(), min_(min), max_(max) {
}

RangeSettingValidator::~RangeSettingValidator() {
}

bool RangeSettingValidator::isValid(const QVariant& value) const {
  bool isOk;
  int intValue = value.toInt(&isOk);
  if (!isOk) {
    qxtLog->warning("int data type expected but not recieved. value=", value);
    return false;
  }
  return (min_.isAbsent() || intValue >= min_.get()) && (max_.isAbsent() || intValue <= max_.get());
}

int RangeSettingValidator::getMin(bool* isOk) const {
  if (isOk != NULL) {
    *isOk = !min_.isAbsent();
  }
  return min_.isAbsent() ? 0 : min_.get();
}

int RangeSettingValidator::getMax(bool* isOk) const {
  if (isOk != NULL) {
    *isOk =  max_.isAbsent();
  }
  return max_.isAbsent() ? 0 : max_.get();
}
