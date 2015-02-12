/* See the file "LICENSE.md" for the full license governing this code. */
#include "Process.h"

#include "Process_p.h"

#include <QKeySequence>

Process::Process()
  : pimpl_(new ProcessPrivate()) {
}

Process::~Process() {
  delete pimpl_;
}

void Process::setAsFocusedWindow() {
  pimpl_->setAsFocusedWindow();
}

void Process::sendKeys(const QKeySequence& keySequence) {
  pimpl_->sendKeys(keySequence);
}
