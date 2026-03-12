/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpservermanager.h"
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextMcpServerManager::TextAutoGenerateTextMcpServerManager(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateText::TextAutoGenerateTextMcpServerManager::~TextAutoGenerateTextMcpServerManager() = default;
#include "moc_textautogeneratetextmcpservermanager.cpp"
