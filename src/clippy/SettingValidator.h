#ifndef SETTINGVALIDATOR_H
#define SETTINGVALIDATOR_H

#include "Optional.h"

#include <QList>

class QVariant;

class SettingValidator
{
public:
  SettingValidator();
  virtual ~SettingValidator();

  virtual bool isValid(const QVariant& value) const = 0;
};

class NoopSettingValidator : public SettingValidator
{
public:
  explicit NoopSettingValidator();
  ~NoopSettingValidator();

  bool isValid(const QVariant&) const;
};

class IntSettingValidator : public SettingValidator
{
private:
  Optional<int> min_;
  Optional<int> max_;

public:
  explicit IntSettingValidator(Optional<int> min = Optional<int>::absent(),
       Optional<int> max = Optional<int>::absent());
  ~IntSettingValidator();

  bool isValid(const QVariant& value) const;

  int getMin(bool* isOk) const;
  int getMax(bool* isOk) const;
};

class ChoiceSettingValidator : public SettingValidator
{
private:
  QList<QVariant> choices_;

public:
  explicit ChoiceSettingValidator(QList<QVariant> choices);
  ~ChoiceSettingValidator();

  bool isValid(const QVariant& value) const;
};

#endif // SETTINGVALIDATOR_H
