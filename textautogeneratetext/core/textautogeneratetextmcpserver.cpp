/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpserver.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextMcpServer::TextAutoGenerateTextMcpServer(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextMcpServer::~TextAutoGenerateTextMcpServer() = default;

#include "moc_textautogeneratetextmcpserver.cpp"
