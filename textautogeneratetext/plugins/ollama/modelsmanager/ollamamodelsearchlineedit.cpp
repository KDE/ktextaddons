/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsearchlineedit.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>

OllamaModelSearchLineEdit::OllamaModelSearchLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setClearButtonEnabled(true);
    setPlaceholderText(i18nc("@info:placeholder", "Search Model…"));
    KLineEditEventHandler::catchReturnKey(this);
}

OllamaModelSearchLineEdit::~OllamaModelSearchLineEdit() = default;

#include "moc_ollamamodelsearchlineedit.cpp"
