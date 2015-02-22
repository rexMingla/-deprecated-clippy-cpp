#include "HotKeyWidget.h"

#include "src/common/Logger.h"
#include "src/settings/SettingItem.h"
#include "src/settings/SettingMetadata.h"

#include <QKeyEvent>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
  Logger log("HotKeyEdit");

  // http://qt-project.org/doc/note_revisions/273/455/view
  QKeySequence keyEventToKeySequence(const QKeyEvent* ke) {
    QString modifier = QString::null;

    if (ke->modifiers() & Qt::ShiftModifier) {
      modifier += "Shift+";
    }
    if (ke->modifiers() & Qt::ControlModifier) {
      modifier += "Ctrl+";
    }
    if (ke->modifiers() & Qt::AltModifier) {
      modifier += "Alt+";
    }
    if (ke->modifiers() & Qt::MetaModifier) {
      modifier += "Meta+";
    }
    QString key = (QString)QKeySequence(ke->key());
    return QKeySequence(modifier + key);
  }
}

HotKeyWidget::HotKeyWidget(SettingItem* item, QWidget* parent)
  : SettingItemWidget(item, parent),
    edit_(new QLineEdit(this)) {
    //clearButton_(new QPushButton(this, "Clear")) {
  setupUi();
  onSettingChanged(item_->value());
}

HotKeyWidget::~HotKeyWidget() {
}

void HotKeyWidget::onSettingChanged(const QVariant& value) {
  keySequence_ = QKeySequence(value.toString());
  updateEdit();
}

bool HotKeyWidget::eventFilter(QObject* obj, QEvent* event) {
  if (obj != edit_) {
    return QObject::eventFilter(obj, event);
  }
  if (event->type() == QEvent::KeyRelease) {
    log.debug("Key press release");
    applyKeyPress();
    return true;
  }
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    keySequence_ = keyEventToKeySequence(keyEvent);
    log.debug("Key press down=", keySequence_);
    updateEdit();
    return true;
  }
  if (event->type() == QEvent::FocusIn) {
    log.debug("focus in..");
    onFocusIn();
    return false;
  }
  if (event->type() == QEvent::FocusOut) {
    log.debug("focus out..");
    onFocusOut();
    return false;
  }
  // standard event processing
  return QObject::eventFilter(obj, event);
}

void HotKeyWidget::setupUi() {
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(edit_);
  //layout->addWidget(clearButton_);

  edit_->setPlaceholderText("Press keys...");
  edit_->installEventFilter(this);
  edit_->setReadOnly(true);
}

void HotKeyWidget::onFocusOut() {
  edit_->setStyleSheet("color: black;");
  // verify change
  updateEdit();
}

void HotKeyWidget::onFocusIn() {
  edit_->setStyleSheet("color: gray; border: 1px solid blue");
  edit_->setText("Press keys...");
}

void HotKeyWidget::updateEdit() {
  if (keySequence_.count()) {
    edit_->setText(keySequence_);
  } else {
    edit_->clear();
  }
}

void HotKeyWidget::applyKeyPress() {
  QString error;
  bool isValid = item_->metadata().isValid(keySequence_, error);
  if (!isValid) {
    QMessageBox::critical(this, "Invalid sequence", error);
  } else {
    edit_->clearFocus();
  }
  log.debug("keySequence=", keySequence_, "isValid=", isValid);
}

