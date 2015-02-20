/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef NOOPMETADATA_H
#define NOOPMETADATA_H

#include "SettingMetadata.h"

/**
 * @brief Metadata that always returns true (added for consistency rather than having a null Metadata)
 */
class NoopSettingMetadata : public SettingMetadata
{
public:
  explicit NoopSettingMetadata(const QVariant& defaultValue);
  ~NoopSettingMetadata();

  bool isValid(const QVariant&) const;
};

#endif // NOOPMETADATA_H
