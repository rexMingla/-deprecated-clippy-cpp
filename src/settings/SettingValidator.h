/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTINGVALIDATOR_H
#define SETTINGVALIDATOR_H

#include "src/global/Optional.h"

#include <QList>

class QVariant;

/**
 * @brief Interface for all validators.
 */
class SettingValidator
{
public:
  SettingValidator();
  virtual ~SettingValidator();

  virtual bool isValid(const QVariant& value) const = 0;
};

#endif // SETTINGVALIDATOR_H
