/*
   SPDX-FileCopyrightText: 2022 Nicolas Fella <nicolas.fella@gmx.de>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratecolorsandmessageviewstyle.h"

#include <QGuiApplication>
using namespace TextAutoGenerateText;
TextAutoGenerateColorsAndMessageViewStyle::TextAutoGenerateColorsAndMessageViewStyle()
{
    regenerateColorScheme();
    qGuiApp->installEventFilter(this);
}

bool TextAutoGenerateColorsAndMessageViewStyle::eventFilter([[maybe_unused]] QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::ApplicationPaletteChange) {
        regenerateColorScheme();
    }
    return false;
}

TextAutoGenerateColorsAndMessageViewStyle &TextAutoGenerateColorsAndMessageViewStyle::self()
{
    static TextAutoGenerateColorsAndMessageViewStyle c;
    return c;
}

KColorScheme TextAutoGenerateColorsAndMessageViewStyle::schemeView() const
{
    return mSchemeView;
}

KColorScheme TextAutoGenerateColorsAndMessageViewStyle::schemeWindow() const
{
    return mSchemeWindow;
}

void TextAutoGenerateColorsAndMessageViewStyle::regenerateColorScheme()
{
    const KColorScheme colorScheme(QPalette::Active, KColorScheme::Window);
    if (!(mSchemeWindow == colorScheme)) {
        mSchemeView = KColorScheme();
        mSchemeWindow = std::move(colorScheme);
        Q_EMIT needToUpdateColors();
    }
}

#include "moc_textautogeneratecolorsandmessageviewstyle.cpp"
