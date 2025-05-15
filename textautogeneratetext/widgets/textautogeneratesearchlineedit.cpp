/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
    connect(mSearchTimer, &QTimer::timeout, this, &TextAutoGenerateSearchLineEdit::slotSearchTimerFired);
    connect(this, &QLineEdit::textChanged, this, &TextAutoGenerateSearchLineEdit::slotSearchTextEdited);
}

TextAutoGenerateSearchLineEdit::~TextAutoGenerateSearchLineEdit() = default;

void TextAutoGenerateSearchLineEdit::slotSearchTimerFired()
{
    mSearchTimer->stop();
    slotTextChanged(text());
}

void TextAutoGenerateSearchLineEdit::slotSearchTextEdited()
{
    if (mSearchTimer->isActive()) {
        mSearchTimer->stop(); // eventually
    }

    mSearchTimer->setSingleShot(true);
    mSearchTimer->start(300ms);
}

void TextAutoGenerateSearchLineEdit::slotTextChanged(const QString &text)
{
    Q_EMIT searchText(text);
}

#include "moc_textautogeneratesearchlineedit.cpp"
