/*
   SPDX-FileCopyrightText: 2022 Nicolas Fella <nicolas.fella@gmx.de>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratecolorsandmessageviewstyle.h"

#include <QApplication>
using namespace TextAutoGenerateText;
TextAutogenerateColorsAndMessageViewStyle::TextAutogenerateColorsAndMessageViewStyle()
{
    regenerateColorScheme();
    qGuiApp->installEventFilter(this);
}

bool TextAutogenerateColorsAndMessageViewStyle::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    if (event->type() == QEvent::ApplicationPaletteChange) {
        regenerateColorScheme();
    }
    return false;
}

TextAutogenerateColorsAndMessageViewStyle &TextAutogenerateColorsAndMessageViewStyle::self()
{
    static TextAutogenerateColorsAndMessageViewStyle c;
    return c;
}

KColorScheme TextAutogenerateColorsAndMessageViewStyle::schemeView() const
{
    return mSchemeView;
}

KColorScheme TextAutogenerateColorsAndMessageViewStyle::schemeWindow() const
{
    return mSchemeWindow;
}

void TextAutogenerateColorsAndMessageViewStyle::regenerateColorScheme()
{
    const KColorScheme colorScheme(QPalette::Active, KColorScheme::Window);
    if (!(mSchemeWindow == colorScheme)) {
        mSchemeView = KColorScheme();
        mSchemeWindow = std::move(colorScheme);
        Q_EMIT needToUpdateColors();
    }
}

#include "moc_textautogeneratecolorsandmessageviewstyle.cpp"
