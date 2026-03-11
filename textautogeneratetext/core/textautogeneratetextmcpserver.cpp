/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpserver.h"
#include <QDebug>
using namespace TextAutoGenerateText;
TextAutoGenerateTextMcpServer::TextAutoGenerateTextMcpServer() = default;

TextAutoGenerateTextMcpServer::~TextAutoGenerateTextMcpServer() = default;

QUrl TextAutoGenerateTextMcpServer::serverUrl() const
{
    return mServerUrl;
}

void TextAutoGenerateTextMcpServer::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

bool TextAutoGenerateTextMcpServer::enabled() const
{
    return mEnabled;
}

void TextAutoGenerateTextMcpServer::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextMcpServer &t)
{
    d.space() << "url:" << t.serverUrl();
    d.space() << "enabled:" << t.enabled();
    return d;
}
