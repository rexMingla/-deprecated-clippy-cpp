#ifndef RANGESETTINGVALIDATOR_H
#define RANGESETTINGVALIDATOR_H

#include "SettingValidator.h"

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
