/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef CHOICEMETADATA_H
#define CHOICEMETADATA_H

#include "SettingMetadata.h"

/**
 * @brief Validates that a settings value comes from one of a predfined set of values.
 */
class ChoiceMetadata : public SettingMetadata
{
private:
  QList<QVariant> choices_;

public:
  explicit ChoiceMetadata(const QVariant& defaultValue, const QList<QVariant>& choices);
  ~ChoiceMetadata();

  bool isValid(const QVariant& value) const;
  const QList<QVariant>& choices() const;
};

#endif // CHOICEMETADATA_H
