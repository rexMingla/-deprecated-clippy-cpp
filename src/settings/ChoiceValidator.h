#ifndef CHOICEVALIDATOR_H
#define CHOICEVALIDATOR_H

#include "SettingValidator.h"

class ChoiceSettingValidator : public SettingValidator
{
private:
  QList<QVariant> choices_;

public:
  explicit ChoiceSettingValidator(QList<QVariant> choices);
  ~ChoiceSettingValidator();

  bool isValid(const QVariant& value) const;
};

#endif // CHOICEVALIDATOR_H
