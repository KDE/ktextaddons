/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemodelsearchlineedit.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
using namespace TextAutoGenerateText;
TextAutoGenerateModelSearchLineEdit::TextAutoGenerateModelSearchLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setClearButtonEnabled(true);
    setPlaceholderText(i18nc("@info:placeholder", "Search Model…"));
    KLineEditEventHandler::catchReturnKey(this);
}

TextAutoGenerateModelSearchLineEdit::~TextAutoGenerateModelSearchLineEdit() = default;

#include "moc_textautogeneratemodelsearchlineedit.cpp"
