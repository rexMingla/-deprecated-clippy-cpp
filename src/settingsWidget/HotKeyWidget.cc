#include "HotKeyWidget.h"

#include "src/common/Logger.h"
#include "src/settings/SettingItem.h"
#include "src/settings/SettingMetadata.h"

#include <QKeyEvent>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>

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
    QString key = QKeySequence(ke->key()).toString();
    return QKeySequence(modifier + key);
  }
}

HotKeyWidget::HotKeyWidget(SettingItem* item, QWidget* parent)
  : SettingItemWidget(item, parent),
    edit_(new QLineEdit(this)),
    clearButton_(new QPushButton("Clear", this)) { // TODO: get clear icon
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
  clearButton_->setToolTip("Remove shortcut");
  connect(clearButton_, SIGNAL(clicked()), SLOT(onClearPressed()));

  QHBoxLayout* layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(4);
  layout->addWidget(edit_);
  layout->addWidget(clearButton_);

  edit_->setMinimumWidth(100);
  edit_->setPlaceholderText("Press keys...");
  edit_->setAlignment(Qt::AlignCenter);
  edit_->installEventFilter(this);
}

void HotKeyWidget::onFocusOut() {
  edit_->setStyleSheet("color: black;");
  updateEdit();
}

void HotKeyWidget::onFocusIn() {
  edit_->setStyleSheet("color: gray;");
  edit_->setText("Press keys...");
}

void HotKeyWidget::updateEdit() {
  edit_->setText(keySequence_);
  clearButton_->setEnabled(!item_->value().toString().isEmpty());
}

void HotKeyWidget::applyKeyPress() {
  QString error;
  bool isValid = item_->metadata().isValid(keySequence_, error);
  if (!isValid) {
    QMessageBox::critical(this, "Invalid sequence", error);
  } else {
    setValue(keySequence_);
    edit_->clearFocus();
  }
  log.debug("keySequence=", keySequence_, "isValid=", isValid);
}

void HotKeyWidget::onClearPressed() {
  log.debug("clear pressed");
  setValue(QKeySequence());
}

