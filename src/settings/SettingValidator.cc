#include "SettingValidator.h"

#include "vendor/qxt/qxtlogger.h"

#include <QVariant>

// SettingValidator
SettingValidator::SettingValidator() {
}

SettingValidator::~SettingValidator() {
}

// NoopSettingValidator
NoopSettingValidator::NoopSettingValidator()
  : SettingValidator() {
}

NoopSettingValidator::~NoopSettingValidator() {
}

bool NoopSettingValidator::isValid(const QVariant&) const {
  return true;
}

// IntSettingValidator
IntSettingValidator::IntSettingValidator(Optional<int> min, Optional<int> max)
  : SettingValidator(), min_(min), max_(max) {
}

IntSettingValidator::~IntSettingValidator() {
}

bool IntSettingValidator::isValid(const QVariant& value) const {
  bool isOk;
  int intValue = value.toInt(&isOk);
  if (!isOk) {
    qxtLog->warning("int data type expected but not recieved. value=", value);
    return false;
  }
  return (min_.isAbsent() || intValue >= min_.get()) && (max_.isAbsent() || intValue <= max_.get());
}

int IntSettingValidator::getMin(bool* isOk) const {
  if (isOk != NULL) {
    *isOk = !min_.isAbsent();
  }
  return min_.isAbsent() ? 0 : min_.get();
}

int IntSettingValidator::getMax(bool* isOk) const {
  if (isOk != NULL) {
    *isOk =  max_.isAbsent();
  }
  return max_.isAbsent() ? 0 : max_.get();
}

ChoiceSettingValidator::ChoiceSettingValidator(QList<QVariant> choices)
  : choices_(choices) {
}

ChoiceSettingValidator::~ChoiceSettingValidator() {
}

bool ChoiceSettingValidator::isValid(const QVariant& value) const {
  // we can't use a set here unfornately as hash can't be resolved for QVariant
  foreach(QVariant choice, choices_) {
    if (choice == value) {
      return true;
    }
  }
  return false;
}
