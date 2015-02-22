/* See the file "LICENSE.md" for the full license governing this code. */
#include "HotKeyMetadata.h"

#include "StandardShortcuts.h"

#include "src/common/Logger.h"

#include <QKeySequence>

namespace {
  Logger log("HotKeyMetadata");

  Qt::KeyboardModifiers ELIGIBLE_MODS = Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier;
  Qt::KeyboardModifiers ALL_MODS = Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier;

  const QString MISSING_REQUIRED_KEY =
      QString("Shortcut must contain one key in combination with at least one of ")
      .append(QKeySequence(Qt::ControlModifier)).append(", ")
      .append(QKeySequence(Qt::AltModifier)).append(" or ")
      .append(QKeySequence(Qt::MetaModifier));


}

HotKeyMetadata::HotKeyMetadata(const QKeySequence& defaultValue, StandardShortcuts* standardShortcuts)
  : SettingMetadata(HOT_KEY, defaultValue),
    standardShortcuts_(standardShortcuts != 0 ? standardShortcuts : new StandardShortcuts(0)) { // TODO: this is lazy DI
}

HotKeyMetadata::~HotKeyMetadata() {
}

bool HotKeyMetadata::isValid(const QVariant& value, QString& error) const {
  if (!value.canConvert<QKeySequence>()) {
    error = QString("Unable to convert value to key sequence. type=%1").arg(value.type());
    return false;
  }
  QKeySequence ks = value.value<QKeySequence>();
  if (ks.count() == 0) {
    return true; // ok. unsetting shortcut
  }

  // only care able the first key (code from QxtGlobalShortcutPrivate::setShortcut)
  int shortcut = ks[0];
  Qt::Key key = Qt::Key((shortcut ^ ALL_MODS) & shortcut);
  Qt::KeyboardModifiers mods = Qt::KeyboardModifiers(shortcut & ELIGIBLE_MODS);
  if (!key || mods == Qt::NoModifier) {
    error = MISSING_REQUIRED_KEY;
    return false;
  }

  // check if one of the standard keys. not ideal or completely correct. It would be much better to
  // actually test check if the key was taken; as described here:
  // http://stackoverflow.com/questions/866056/how-do-i-programmatically-get-the-shortcut-keys-reserved-by-mac-os-x
  QString keyName;
  if (standardShortcuts_->isStandardShortcut(ks, keyName)) {
    error = QString("Shortcut already taken by %1").arg(keyName);
  }
  return error.isEmpty();
}
