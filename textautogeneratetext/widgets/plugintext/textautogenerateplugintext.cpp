/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateplugintext.h"

using namespace TextAutoGenerateText;
TextAutoGeneratePluginText::TextAutoGeneratePluginText(QObject *parent)
    : QObject{parent}
{
}

TextAutoGeneratePluginText::~TextAutoGeneratePluginText() = default;

bool TextAutoGeneratePluginText::enabled() const
{
    return mEnabled;
}

void TextAutoGeneratePluginText::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

bool TextAutoGeneratePluginText::hasConfigureDialog() const
{
    return false;
}

void TextAutoGeneratePluginText::showConfigureDialog([[maybe_unused]] QWidget *parent) const
{
}

#include "moc_textautogenerateplugintext.cpp"
