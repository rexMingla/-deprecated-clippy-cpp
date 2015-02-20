/* See the file "LICENSE.md" for the full license governing this code. */
#include "ChoiceMetadata.h"

#include <QVariant>

ChoiceMetadata::ChoiceMetadata(const QVariant& defaultValue, const QList<QVariant>& choices)
  : SettingMetadata(defaultValue),
    choices_(choices) {
}

ChoiceMetadata::~ChoiceMetadata() {
}

bool ChoiceMetadata::isValid(const QVariant& value) const {
  // we can't use a set here unfornately as hash can't be resolved for QVariant
  foreach (const QVariant& choice, choices_) {
    if (choice == value) {
      return true;
    }
  }
  return false;
}

const QList<QVariant>&ChoiceMetadata::choices() const {
  return choices_;
}
