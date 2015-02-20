/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef SETTINGMETADATA_H
#define SETTINGMETADATA_H

#include <QString>
#include <QVariant>

/**
 * @brief Interface for all validators.
 */
class SettingMetadata
{
private:
  QVariant defaultValue_;
  QString displayName_;
  bool isHidden_;

public:
  SettingMetadata(const QVariant& defaultValue);
  virtual ~SettingMetadata();

  void setDisplayName(const QString& name);
  void setIsHidden(bool isHidden);

  const QString& displayName() const;
  bool isHidden() const;
  const QVariant& defaultValue() const;
  QVariant::Type type() const;

  virtual bool isValid(const QVariant& value) const = 0;
};

#endif // SETTINGMETADATA_H
