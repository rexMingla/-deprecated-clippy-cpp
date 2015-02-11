#ifndef SETTINGVALIDATOR_H
#define SETTINGVALIDATOR_H

#include "src/global/Optional.h"

#include <QList>

class QVariant;

class SettingValidator
{
public:
  SettingValidator();
  virtual ~SettingValidator();

  virtual bool isValid(const QVariant& value) const = 0;
};

#endif // SETTINGVALIDATOR_H
