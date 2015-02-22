/* See the file "LICENSE.md" for the full license governing this code. */
#include "StandardShortcuts.h"

StandardShortcuts::StandardShortcuts(QObject* parent)
  : QObject(parent),
    standardKeys_(createList()) {
}

StandardShortcuts::~StandardShortcuts() {
}

bool StandardShortcuts::isStandardShortcut(const QKeySequence& sequence, QString& keyName) const {
  foreach (const StandardKey& key, standardKeys_) {
    foreach (QKeySequence ks, QKeySequence::keyBindings(key.key_)) {
      if (ks == sequence) {
        keyName = key.name_;
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief StandardShortcuts::createList
 * @return list of key names we are concerned with. Note the full list has been cut down to the ones that make sense.
 */
QList<StandardShortcuts::StandardKey> StandardShortcuts::createList() {
  QList<StandardShortcuts::StandardKey> ret;
  ret << StandardKey(QKeySequence::HelpContents, "Help Contents");
  ret << StandardKey(QKeySequence::WhatsThis, "Whats This");
  ret << StandardKey(QKeySequence::Open, "Open");
  ret << StandardKey(QKeySequence::Close, "Close");
  ret << StandardKey(QKeySequence::Save, "Save");
  ret << StandardKey(QKeySequence::New, "New");
  ret << StandardKey(QKeySequence::Delete, "Delete");
  ret << StandardKey(QKeySequence::Cut, "Cut");
  ret << StandardKey(QKeySequence::Copy, "Copy");
  ret << StandardKey(QKeySequence::Paste, "Paste");
  ret << StandardKey(QKeySequence::Undo, "Undo");
  ret << StandardKey(QKeySequence::Redo, "Redo");
  ret << StandardKey(QKeySequence::SaveAs, "Save As");
  return ret;
}

