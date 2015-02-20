/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef HOTKEYSETTING_H
#define HOTKEYSETTING_H

#include "SettingMetadata.h"

class QKeySequence;

/**
 * @brief Metadata of hot key entry
 *
 *        TODO: not yet implemented
 */
class HotKeyMetadata : public SettingMetadata
{
public:
  HotKeyMetadata(const QKeySequence& defaultValue);
  ~HotKeyMetadata();

  bool isValid(const QVariant& value) const;
};

#endif // HOTKEYSETTING_H
