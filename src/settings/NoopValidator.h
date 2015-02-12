/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef NOOPVALIDATOR_H
#define NOOPVALIDATOR_H

#include "SettingValidator.h"

class NoopSettingValidator : public SettingValidator
{
public:
  explicit NoopSettingValidator();
  ~NoopSettingValidator();

  bool isValid(const QVariant&) const;
};

#endif // NOOPVALIDATOR_H
