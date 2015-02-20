/* See the file "LICENSE.md" for the full license governing this code. */
#include "ChoiceMetadata.h"

#include <QStringList>
#include <QVariant>

ChoiceMetadata::ChoiceMetadata(const QVariant& defaultValue, const QList<QVariant>& choices)
  : SettingMetadata(CHOICE, defaultValue),
    choices_(choices) {
}

ChoiceMetadata::~ChoiceMetadata() {
}

bool ChoiceMetadata::isValid(const QVariant& value, QString& error) const {
  // we can't use a set here unfornately as hash can't be resolved for QVariant
  foreach (const QVariant& choice, choices_) {
    if (choice == value) {
      return true;
    }
  }
  QStringList list;
  foreach (const QVariant& choice, choices_) {
    list << choice.toString();
  }
  error = QString("choice must be one of the following [%1].").arg(list.join(","));
  return false;
}

const QList<QVariant>&ChoiceMetadata::choices() const {
  return choices_;
}
