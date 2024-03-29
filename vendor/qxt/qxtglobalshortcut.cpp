/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtGui module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/
#include "qxtglobalshortcut.h"
#include "qxtglobalshortcut_p.h"
#include <QAbstractEventDispatcher>
#include <QtDebug>

bool QxtGlobalShortcutPrivate::error = false;
#ifndef Q_WS_MAC
int QxtGlobalShortcutPrivate::ref = 0;
QAbstractEventDispatcher::EventFilter QxtGlobalShortcutPrivate::prevEventFilter = 0;
#endif // Q_WS_MAC
QHash<QPair<quint32, quint32>, QxtGlobalShortcut*> QxtGlobalShortcutPrivate::shortcuts;

QxtGlobalShortcutPrivate::QxtGlobalShortcutPrivate() : enabled(true), key(Qt::Key(0)), mods(Qt::NoModifier)
{
#ifndef Q_WS_MAC
    if (!ref++)
        prevEventFilter = QAbstractEventDispatcher::instance()->setEventFilter(eventFilter);
#endif // Q_WS_MAC
}

QxtGlobalShortcutPrivate::~QxtGlobalShortcutPrivate()
{
#ifndef Q_WS_MAC
    if (!--ref)
        QAbstractEventDispatcher::instance()->setEventFilter(prevEventFilter);
#endif // Q_WS_MAC
}

bool QxtGlobalShortcutPrivate::setShortcut(const QKeySequence& shortcut)
{
    Qt::KeyboardModifiers allMods = Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier;
    key = shortcut.isEmpty() ? Qt::Key(0) : Qt::Key((shortcut[0] ^ allMods) & shortcut[0]);
    mods = shortcut.isEmpty() ? Qt::KeyboardModifiers(0) : Qt::KeyboardModifiers(shortcut[0] & allMods);
    const quint32 nativeKey = nativeKeycode(key);
    const quint32 nativeMods = nativeModifiers(mods);
    const bool res = registerShortcut(nativeKey, nativeMods);
    if (res)
    {
        qDebug() << "QxtGlobalShortcut registered:" << QKeySequence(key + mods).toString();
        shortcuts.insert(qMakePair(nativeKey, nativeMods), &qxt_p());
    }
    else
        qWarning() << "QxtGlobalShortcut failed to register:" << QKeySequence(key + mods).toString();
    return res;
}

bool QxtGlobalShortcutPrivate::unsetShortcut()
{
    if (key == 0) {
      qDebug() << "QxtGlobalShortcut shortcut was not previously registered. doing nothing.";
      return true;
    }
    bool res = false;
    const quint32 nativeKey = nativeKeycode(key);
    const quint32 nativeMods = nativeModifiers(mods);
    if (shortcuts.value(qMakePair(nativeKey, nativeMods)) == &qxt_p())
        res = unregisterShortcut(nativeKey, nativeMods);
    if (res)
    {
        qDebug() << "QxtGlobalShortcut unregistered:" << QKeySequence(key + mods).toString();
        shortcuts.remove(qMakePair(nativeKey, nativeMods));
    }
    else
        qWarning() << "QxtGlobalShortcut failed to unregister:" << QKeySequence(key + mods).toString();
    //key = Qt::Key(0);
    //mods = Qt::KeyboardModifiers(0);
    return res;
}

void QxtGlobalShortcutPrivate::activateShortcut(quint32 nativeKey, quint32 nativeMods)
{
    QxtGlobalShortcut* shortcut = shortcuts.value(qMakePair(nativeKey, nativeMods));
    if (shortcut && shortcut->isEnabled())
        emit shortcut->activated();
}

/*!
    \class QxtGlobalShortcut
    \inmodule QxtGui
    \brief The QxtGlobalShortcut class provides a global shortcut aka "hotkey".

    A global shortcut triggers even if the application is not active. This
    makes it easy to implement applications that react to certain shortcuts
    still if some other application is active or if the application is for
    example minimized to the system tray.

    Example usage:
    \code
    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(window);
    connect(shortcut, SIGNAL(activated()), window, SLOT(toggleVisibility()));
    shortcut->setShortcut(QKeySequence("Ctrl+Shift+F12"));
    \endcode

    \bold {Note:} Since Qxt 0.6 QxtGlobalShortcut no more requires QxtApplication.
 */

/*!
    \fn QxtGlobalShortcut::activated()

    This signal is emitted when the user types the shortcut's key sequence.

    \sa shortcut
 */

/*!
    Constructs a new QxtGlobalShortcut with \a parent.
 */
QxtGlobalShortcut::QxtGlobalShortcut(QObject* parent)
        : QObject(parent)
{
    QXT_INIT_PRIVATE(QxtGlobalShortcut);
}

/*!
    Constructs a new QxtGlobalShortcut with \a shortcut and \a parent.
 */
QxtGlobalShortcut::QxtGlobalShortcut(const QKeySequence& shortcut, QObject* parent)
        : QObject(parent)
{
    QXT_INIT_PRIVATE(QxtGlobalShortcut);
    setShortcut(shortcut);
}

/*!
    Destructs the QxtGlobalShortcut.
 */
QxtGlobalShortcut::~QxtGlobalShortcut()
{
    if (qxt_d().enabled)
        qxt_d().unsetShortcut();
}

/*!
    \property QxtGlobalShortcut::shortcut
    \brief the shortcut key sequence

    \bold {Note:} Notice that corresponding key press and release events are not
    delivered for registered global shortcuts even if they are disabled.
    Also, comma separated key sequences are not supported.
    Only the first part is used:

    \code
    qxtShortcut->setShortcut(QKeySequence("Ctrl+Alt+A,Ctrl+Alt+B"));
    Q_ASSERT(qxtShortcut->shortcut() == QKeySequence("Ctrl+Alt+A"));
    \endcode
 */
QKeySequence QxtGlobalShortcut::shortcut() const
{
    return QKeySequence(qxt_d().key | qxt_d().mods);
}

bool QxtGlobalShortcut::setShortcut(const QKeySequence& shortcut)
{
    if (isEnabled())
        qxt_d().unsetShortcut();
    return qxt_d().setShortcut(shortcut);
}

/*!
    \property QxtGlobalShortcut::enabled
    \brief whether the shortcut is enabled

    A disabled shortcut does not get activated.

    The default value is \c true.

    \sa setDisabled()
 */
bool QxtGlobalShortcut::isEnabled() const
{
    return qxt_d().enabled;
}

void QxtGlobalShortcut::setEnabled(bool enabled)
{
    if (qxt_d().enabled == enabled)
      return ;
    qxt_d().enabled = enabled;
    if (enabled)
      qxt_d().setShortcut(QKeySequence(qxt_d().key + qxt_d().mods));
    else
      qxt_d().unsetShortcut();
}

/*!
    Sets the shortcut \a disabled.

    \sa enabled
 */
void QxtGlobalShortcut::setDisabled(bool disabled)
{
    setEnabled(!disabled);
}
