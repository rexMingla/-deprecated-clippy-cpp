/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef HOTKEYSETTING_H
#define HOTKEYSETTING_H

#include "SettingMetadata.h"

class StandardShortcuts;
class QKeySequence;

/**
 * @brief Data associated with hot key seqeuence
 */
class HotKeyMetadata : public SettingMetadata
{
private:
  StandardShortcuts* standardShortcuts_;

public:
  HotKeyMetadata(const QKeySequence& defaultValue, StandardShortcuts* standardShortcuts = 0);
  ~HotKeyMetadata();

  bool isValid(const QVariant& value, QString& error) const;
};

#endif // HOTKEYSETTING_H
