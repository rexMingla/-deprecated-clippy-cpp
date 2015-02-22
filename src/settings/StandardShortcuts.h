#ifndef STANDARDSHORTCUTS_H
#define STANDARDSHORTCUTS_H

#include "src/common/Optional.h"

#include <QKeySequence>
#include <QList>
#include <QObject>
#include <QString>

class QKeySequence;

/**
 * @brief Compares the key name against the standard keys as defind by QKeySequence::StandardKey
 */
class StandardShortcuts : public QObject
{
  Q_OBJECT
private:
  struct StandardKey {
    QKeySequence::StandardKey key_;
    QString name_;

    StandardKey(QKeySequence::StandardKey key, const QString& name) : key_(key), name_(name) {
    }
  };

  QList<StandardKey> standardKeys_;

public:
  StandardShortcuts(QObject* parent = 0);
  ~StandardShortcuts();

  // if the key is a standard key, keyName is set to the name of the shortcut. ie. paste.
  bool isStandardShortcut(const QKeySequence& sequence, QString& keyName) const;

private:
  static QList<StandardKey> createList();
};

#endif // STANDARDSHORTCUTS_H
