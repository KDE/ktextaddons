/*
   SPDX-FileCopyrightText: 2022 Nicolas Fella <nicolas.fella@gmx.de>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textutilscolorsandmessageviewstyle.h"

#include <QGuiApplication>
using namespace TextUtils;
TextUtilsColorsAndMessageViewStyle::TextUtilsColorsAndMessageViewStyle()
{
    regenerateColorScheme();
    qGuiApp->installEventFilter(this);
}

bool TextUtilsColorsAndMessageViewStyle::eventFilter([[maybe_unused]] QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::ApplicationPaletteChange) {
        regenerateColorScheme();
    }
    return false;
}

TextUtilsColorsAndMessageViewStyle &TextUtilsColorsAndMessageViewStyle::self()
{
    static TextUtilsColorsAndMessageViewStyle c;
    return c;
}

KColorScheme TextUtilsColorsAndMessageViewStyle::schemeView() const
{
    return mSchemeView;
}

KColorScheme TextUtilsColorsAndMessageViewStyle::schemeWindow() const
{
    return mSchemeWindow;
}

void TextUtilsColorsAndMessageViewStyle::regenerateColorScheme()
{
    const KColorScheme colorScheme(QPalette::Active, KColorScheme::Window);
    if (!(mSchemeWindow == colorScheme)) {
        mSchemeView = KColorScheme();
        mSchemeWindow = colorScheme;
        Q_EMIT needToUpdateColors();
    }
}

#include "moc_textutilscolorsandmessageviewstyle.cpp"
