/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef NOOPMETADATA_H
#define NOOPMETADATA_H

#include "SettingMetadata.h"

class QVariant;

class NoopMetadata : public SettingMetadata
{
public:
  NoopMetadata(const QVariant& defaultValue);
  ~NoopMetadata();

  bool isValid(const QVariant& value, QString& error) const;
};

#endif // NOOPMETADATA_H
