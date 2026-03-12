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

QString TextAutoGenerateTextMcpServer::name() const
{
    return mName;
}

void TextAutoGenerateTextMcpServer::setName(const QString &newName)
{
    mName = newName;
}

QByteArray TextAutoGenerateTextMcpServer::identifier() const
{
    return mIdentifier;
}

void TextAutoGenerateTextMcpServer::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

void TextAutoGenerateTextMcpServer::load(const KConfigGroup &config)
{
    // TODO
}

void TextAutoGenerateTextMcpServer::save(KConfigGroup &config)
{
    // TODO
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextMcpServer &t)
{
    d.space() << "url:" << t.serverUrl();
    d.space() << "enabled:" << t.enabled();
    d.space() << "name:" << t.name();
    d.space() << "identifier:" << t.identifier();
    return d;
}
