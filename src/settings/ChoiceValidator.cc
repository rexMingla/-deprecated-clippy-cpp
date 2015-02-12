/* See the file "LICENSE.md" for the full license governing this code. */
#include "ChoiceValidator.h"

#include <QVariant>

ChoiceSettingValidator::ChoiceSettingValidator(QList<QVariant> choices)
  : choices_(choices) {
}

ChoiceSettingValidator::~ChoiceSettingValidator() {
}

bool ChoiceSettingValidator::isValid(const QVariant& value) const {
  // we can't use a set here unfornately as hash can't be resolved for QVariant
  foreach (const QVariant& choice, choices_) {
    if (choice == value) {
      return true;
    }
  }
  return false;
}
