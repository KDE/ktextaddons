/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchlineedit.h"
#include <QTimer>
#include <chrono>

using namespace std::chrono_literals;
using namespace TextAutoGenerateText;
TextAutoGenerateSearchLineEdit::TextAutoGenerateSearchLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , mSearchTimer(new QTimer(this))
{
    mSearchTimer->setSingleShot(true);
    mSearchTimer->setInterval(500ms);
    connect(mSearchTimer, &QTimer::timeout, this, &TextAutoGenerateSearchLineEdit::slotSearchTimerFired);
    connect(this, &QLineEdit::textChanged, this, &TextAutoGenerateSearchLineEdit::slotSearchTextEdited);
}

TextAutoGenerateSearchLineEdit::~TextAutoGenerateSearchLineEdit() = default;

void TextAutoGenerateSearchLineEdit::slotSearchTimerFired()
{
    slotTextChanged(text());
}

void TextAutoGenerateSearchLineEdit::slotSearchTextEdited()
{
    mSearchTimer->start();
}

void TextAutoGenerateSearchLineEdit::slotTextChanged(const QString &text)
{
    if (const QString trimmedStr = text.trimmed(); !trimmedStr.isEmpty()) {
        Q_EMIT searchText(trimmedStr);
    }
}

#include "moc_textautogeneratesearchlineedit.cpp"
