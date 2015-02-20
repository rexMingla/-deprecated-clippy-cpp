/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef RANGE_METADATA_H
#define RANGE_METADATA_H

#include "SettingMetadata.h"

#include <QVariant>

/**
 * @brief Verifies that a setting value is within a defined range.
 */
class RangeMetadata : public SettingMetadata
{
private:
  QVariant min_;
  QVariant max_;

public:
  RangeMetadata(const QVariant& defaultValue, const QVariant& min, const QVariant& max);
  ~RangeMetadata();

  bool isValid(const QVariant& value) const;

  const QVariant& min() const;
  const QVariant& max() const;
};

#endif // RANGE_METADATA_H
