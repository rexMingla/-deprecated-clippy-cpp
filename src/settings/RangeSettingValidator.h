/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef RANGESETTINGVALIDATOR_H
#define RANGESETTINGVALIDATOR_H

#include "SettingValidator.h"

/**
 * @brief Verifies that a setting value is within a defined range.
 *
 *        The Optionals are probably overkill (as it settings will probably always have upper and lower bounds).
 *        No effort has been make to make this generic either. ie. floats would not be supported.
 */
class RangeSettingValidator : public SettingValidator
{
private:
  Optional<int> min_;
  Optional<int> max_;

public:
  explicit RangeSettingValidator(Optional<int> min = Optional<int>::absent(),
       Optional<int> max = Optional<int>::absent());
  ~RangeSettingValidator();

  bool isValid(const QVariant& value) const;

  int getMin(bool* isOk = 0) const;
  int getMax(bool* isOk = 0) const;
};

#endif // RANGESETTINGVALIDATOR_H
