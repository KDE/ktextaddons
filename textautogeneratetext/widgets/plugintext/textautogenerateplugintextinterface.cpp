/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateplugintextinterface.h"

using namespace TextAutoGenerateText;
TextAutoGeneratePluginTextInterface::TextAutoGeneratePluginTextInterface(QObject *parent)
    : QObject{parent}
{
}

TextAutoGeneratePluginTextInterface::~TextAutoGeneratePluginTextInterface() = default;

#include "moc_textautogenerateplugintextinterface.cpp"
