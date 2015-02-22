/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef BOOL_METADATA_H
#define BOOL_METADATA_H

#include "SettingMetadata.h"

/**
 * @brief Metadata that always returns true (added for consistency rather than having a null Metadata)
 */
class BoolMetadata : public SettingMetadata
{
public:
  explicit BoolMetadata(const QVariant& defaultValue);
  ~BoolMetadata();

  bool isValid(const QVariant&value, QString& error) const;
};

#endif // BOOL_METADATA_H
