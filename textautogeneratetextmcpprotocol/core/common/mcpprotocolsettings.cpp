/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsettings.h"
#include <KConfigGroup>
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSettings::McpProtocolSettings() = default;

McpProtocolSettings::~McpProtocolSettings() = default;

QString McpProtocolSettings::command() const
{
    return mCommand;
}

void McpProtocolSettings::setCommand(const QString &newCommand)
{
    mCommand = newCommand;
}

QString McpProtocolSettings::arguments() const
{
    return mArguments;
}

void McpProtocolSettings::setArguments(const QString &newArguments)
{
    mArguments = newArguments;
}

QMap<QString, QString> McpProtocolSettings::environments() const
{
    return mEnvironments;
}

void McpProtocolSettings::setEnvironments(const QMap<QString, QString> &newEnvironments)
{
    mEnvironments = newEnvironments;
}

QUrl McpProtocolSettings::serverUrl() const
{
    return mServerUrl;
}

void McpProtocolSettings::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &t)
{
    d.space() << "serverUrl" << t.serverUrl();
    d.space() << "environments [";
    const auto envs = t.environments();
    for (auto it = envs.constBegin(); it != envs.constEnd(); ++it) {
        d << it.key() << ":" << it.value();
        if (std::next(it) != envs.constEnd()) {
            d << ", ";
        }
    }
    d << "]";
    d.space() << "arguments" << t.arguments();
    d.space() << "command" << t.command();
    return d;
}

void McpProtocolSettings::load(const KConfigGroup &config)
{
    mServerUrl = config.readEntry("ServerUrl", QUrl());
    mCommand = config.readEntry("Command", QString());
    mArguments = config.readEntry("Arguments", QString());
    // TODO mEnvironments
}

void McpProtocolSettings::save(KConfigGroup &config) const
{
    if (!mCommand.isEmpty()) {
        config.writeEntry(u"Command"_s, mCommand);
    }
    if (!mArguments.isEmpty()) {
        config.writeEntry(u"Arguments"_s, mArguments);
    }
    if (!mServerUrl.isEmpty()) {
        config.writeEntry(u"ServerUrl"_s, mServerUrl);
    }
    // TODO mEnvironments
}

bool McpProtocolSettings::isValid() const
{
    return (mServerUrl.isValid()) || (!mCommand.isEmpty());
}
