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
public:
  enum Type {
    BOOL,
    CHOICE,
    HOT_KEY,
    NO_OP,
    RANGE
  };
private:
  Type type_;
  QVariant defaultValue_;
  QString displayName_;
  bool isHidden_;

public:
  SettingMetadata(Type type, const QVariant& defaultValue);
  virtual ~SettingMetadata();

  void setDisplayName(const QString& name);
  void setIsHidden(bool isHidden);

  const QString& displayName() const;
  bool isHidden() const;
  const QVariant& defaultValue() const;
  Type type() const;

  bool isValid(const QVariant& value) const;
  virtual bool isValid(const QVariant& value, QString& error) const = 0;
};

#endif // SETTINGMETADATA_H
