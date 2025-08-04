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

#include "moc_textautogenerateplugintext.cpp"
