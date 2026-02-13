/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamalogtextedit.h"

OllamaLogTextEdit::OllamaLogTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    setReadOnly(true);
}

OllamaLogTextEdit::~OllamaLogTextEdit() = default;

#include "moc_ollamalogtextedit.cpp"
