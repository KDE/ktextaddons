/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamalogtextedit.h"
#include "ollamasyntaxhighlighter.h"

OllamaLogTextEdit::OllamaLogTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    new OllamaSyntaxHighlighter(document());
    setReadOnly(true);
}

OllamaLogTextEdit::~OllamaLogTextEdit() = default;

#include "moc_ollamalogtextedit.cpp"
