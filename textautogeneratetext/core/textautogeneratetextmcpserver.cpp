/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpserver.h"
#include "core/textautogeneratetextutils.h"
#include <QDebug>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextMcpServer::TextAutoGenerateTextMcpServer() = default;

TextAutoGenerateTextMcpServer::~TextAutoGenerateTextMcpServer() = default;

void TextAutoGenerateTextMcpServer::createUniqueIdentifier()
{
    mIdentifier = TextAutoGenerateTextUtils::generateUUid();
}

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
    mEnabled = config.readEntry("Enabled", true);
    mName = config.readEntry("Name", QString());
    mIdentifier = config.readEntry("Id", QByteArray());
    mServerUrl = config.readEntry("ServerUrl", QUrl());
}

void TextAutoGenerateTextMcpServer::save(KConfigGroup &config)
{
    config.writeEntry(u"ServerUrl"_s, mServerUrl);
    config.writeEntry(u"Id"_s, mIdentifier);
    config.writeEntry(u"Name"_s, mName);
    config.writeEntry(u"Enabled"_s, mEnabled);
}

bool TextAutoGenerateTextMcpServer::isValid() const
{
    return !mIdentifier.isEmpty() && !mName.isEmpty() && !mServerUrl.isEmpty();
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextMcpServer &t)
{
    d.space() << "url:" << t.serverUrl();
    d.space() << "enabled:" << t.enabled();
    d.space() << "name:" << t.name();
    d.space() << "identifier:" << t.identifier();
    return d;
}
