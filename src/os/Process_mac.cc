/* See the file "LICENSE.md" for the full license governing this code. */
#include "Process_p.h"

//#include "OsxKeyMapper.h"
#include "vendor/qxt/qxtlogger.h"
#include "vendor/qxt/qxtglobalshortcut_p.h"

#include <ApplicationServices/ApplicationServices.h>
#include <QKeySequence>

namespace {
  static const int BUFFER_SIZE = 256;

  static Qt::KeyboardModifiers ALL_MODS = Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier;

  QString CFStringRefToQString(const CFStringRef& ref, int bufferSize) {
    char* buffer = new char[bufferSize];
    CFStringGetCString(ref, buffer, bufferSize, 0);
    QString ret(buffer);
    delete[] buffer;
    return ret;
  }

  // reference: https://developer.apple.com/library/mac/documentation/Carbon/Reference/QuartzEventServicesRef/index.html#//apple_ref/c/tdef/CGEventFlags
  quint32 nativeModifiers(Qt::KeyboardModifiers modifiers) {
    quint32 native = 0;
    if (modifiers & Qt::ShiftModifier) {
      native |= kCGEventFlagMaskShift;
    }
    if (modifiers & Qt::ControlModifier) {
      native |= kCGEventFlagMaskCommand;
    }
    if (modifiers & Qt::AltModifier) {
      native |= kCGEventFlagMaskAlternate;
    }
    if (modifiers & Qt::MetaModifier) {
      native |= kCGEventFlagMaskControl; // ?
    }
    if (modifiers & Qt::KeypadModifier) {
      native |= kCGEventFlagMaskNumericPad; // ?
    }
    return native;
  }
}

ProcessPrivate::ProcessPrivate()
  : psn_(new ProcessSerialNumber()) {

  OSStatus err = GetFrontProcess(psn_);
  qxtLog->debug("GetFrontProcess processSerialNumber={",
      (qulonglong) psn_->lowLongOfPSN, ",", (qulonglong) psn_->highLongOfPSN, "} response=", (int) err);
  if (err != noErr) {
    return ;
  }

  CFStringRef processName = NULL;
  err = CopyProcessName(psn_, &processName);
  processName_ = CFStringRefToQString(processName, BUFFER_SIZE);
  CFRelease(processName);
  qxtLog->debug("GetFrontProcess processName=", processName_);
}

ProcessPrivate::~ProcessPrivate() {
  delete psn_;
}

void ProcessPrivate::setAsFocusedWindow() {
  if (!isValid()) {
    qxtLog->info("setAsFocusedWindow: no current process. ignoring command");
    return ;
  }

  OSStatus err = SetFrontProcess(psn_);
  qxtLog->debug("SetFrontProcess processName=", processName_, " response=", (int) err);
}

void ProcessPrivate::sendKeys(const QKeySequence& keySequence) {
  if (!isValid()) {
    qxtLog->info("sendKeys: no current process. ignoring command");
    return ;
  }
  qxtLog->debug("sendKeys keys=", keySequence);
  if (keySequence.isEmpty()) {
    qxtLog->warning("ignoring keySequence as it is empty");
    return ;
  }

  Qt::Key key = Qt::Key((keySequence[0] ^ ALL_MODS) & keySequence[0]);
  Qt::KeyboardModifiers mods = Qt::KeyboardModifiers(keySequence[0] & ALL_MODS);
  CGKeyCode keyCode = QxtGlobalShortcutPrivate::nativeKeycode(key);
  CGEventFlags modifiers = ::nativeModifiers(mods);

  CGEventRef keyDown = CGEventCreateKeyboardEvent(NULL, keyCode, true);
  CGEventSetFlags(keyDown, modifiers);
  CGEventRef keyUp = CGEventCreateKeyboardEvent(NULL, keyCode, false);
  CGEventSetFlags(keyUp, modifiers);

  qxtLog->debug("sending keys=", keyCode, " modifiers=", modifiers);
  CGEventPostToPSN(psn_, keyDown);
  CGEventPostToPSN(psn_, keyUp);
  qxtLog->debug("keys sent=", keyCode);

  CFRelease(keyDown);
  CFRelease(keyUp);
}

bool ProcessPrivate::isValid() const {
  return !processName_.isEmpty();
}
