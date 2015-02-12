/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef HOTKEYSETTINGVALIDATOR_H
#define HOTKEYSETTINGVALIDATOR_H

#include "SettingValidator.h"

class HotKeySettingValidator : public SettingValidator
{
public:
  HotKeySettingValidator();
  ~HotKeySettingValidator();

  bool isValid(const QVariant& value) const;
};

#endif // HOTKEYSETTINGVALIDATOR_H
