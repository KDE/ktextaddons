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

QUrl TextAutoGenerateTextMcpServer::serverUrl() const
{
    return mServerUrl;
}

void TextAutoGenerateTextMcpServer::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

#include "moc_textautogeneratetextmcpserver.cpp"
