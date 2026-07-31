/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "loaddialogsizeutils.h"
#include "textaddonswidgets_debug.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QScreen>
#include <QWindow>

void TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(QWidget *w, const QString &key, int width, int height)
{
    if (!w || !w->windowHandle()) {
        qCWarning(TEXTADDONSWIDGETS_LOG) << "widget is not define or windowHandle not defined. It's a bug";
        return;
    }
    if (KSharedConfig::openStateConfig()->hasGroup(key)) {
        const KConfigGroup group(KSharedConfig::openStateConfig(), key);
        KWindowConfig::restoreWindowSize(w->windowHandle(), group);
        w->resize(w->windowHandle()->size()); // workaround for QTBUG-40584
    } else {
        const qreal scaleFactor = w->windowHandle()->screen()->devicePixelRatio();
        w->windowHandle()->resize(QSize(width * scaleFactor, height * scaleFactor));
    }
}
