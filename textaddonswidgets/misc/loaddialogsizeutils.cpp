/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "loaddialogsizeutils.h"
#include "textaddonswidgets_debug.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialog>
#include <QEvent>
#include <QPointer>
#include <QWindow>

void TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(QWidget *w, const QString &key, int width, int height)
{
    if (!w || !w->windowHandle()) {
        qCWarning(TEXTADDONSWIDGETS_LOG) << "widget is not define or windowHandle not defined. It's a bug";
        return;
    }
    // QWindow::resize() already works in device independent pixels, so the default
    // size must not be multiplied by the device pixel ratio. Applying it before
    // restoreWindowSize() also lets KWindowConfig record it as the initial size, and
    // keeps it in effect when the group exists without an entry for the current screen.
    w->windowHandle()->resize(QSize(width, height));
    const KConfigGroup group(KSharedConfig::openStateConfig(), key);
    KWindowConfig::restoreWindowSize(w->windowHandle(), group);
    w->resize(w->windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAddonsWidgets::LoadDialogSizeUtils::saveDialogSize(QWidget *w, const QString &key)
{
    if (!w || !w->windowHandle()) {
        qCWarning(TEXTADDONSWIDGETS_LOG) << "widget is not define or windowHandle not defined. It's a bug";
        return;
    }
    KConfigGroup group(KSharedConfig::openStateConfig(), key);
    KWindowConfig::saveWindowSize(w->windowHandle(), group);
    group.sync();
}

namespace
{
// Restores the dialog size on the first (non spontaneous) show and stores it
// again when the dialog is destroyed. Installed as an event filter so that any
// QDialog subclass can be managed without changing its base class.
class DialogSizeManager : public QObject
{
public:
    DialogSizeManager(QDialog *dialog, const QString &key, QSize defaultSize)
        : QObject(dialog)
        , mDialog(dialog)
        , mKey(key)
        , mDefaultSize(defaultSize)
    {
        dialog->installEventFilter(this);
    }

    ~DialogSizeManager() override
    {
        // The dialog was never shown: there is no size worth storing.
        if (mInitialized && mDialog && mDialog->windowHandle()) {
            TextAddonsWidgets::LoadDialogSizeUtils::saveDialogSize(mDialog, mKey);
        }
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (watched == mDialog && event->type() == QEvent::Show && !event->spontaneous() && !mInitialized) {
            mInitialized = true;
            TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(mDialog, mKey, mDefaultSize.width(), mDefaultSize.height());
        }
        return QObject::eventFilter(watched, event);
    }

private:
    const QPointer<QDialog> mDialog;
    const QString mKey;
    const QSize mDefaultSize;
    bool mInitialized = false;
};
}

void TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(QDialog *dialog, const QString &key, QSize defaultSize)
{
    if (!dialog) {
        qCWarning(TEXTADDONSWIDGETS_LOG) << "dialog is not defined. It's a bug";
        return;
    }
    new DialogSizeManager(dialog, key, defaultSize);
}
