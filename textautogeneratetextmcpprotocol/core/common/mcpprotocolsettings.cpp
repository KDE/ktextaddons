/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsettings.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
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
    mHeaders = config.readEntry("Headers", QStringList());
    mEnvironments.clear();
    const QStringList environments = config.readEntry("Environments", QStringList());
    for (const QString &environment : environments) {
        const qsizetype index = environment.indexOf(u'=');
        if (index <= 0) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid environment entry, expected \"KEY=VALUE\": " << environment;
            continue;
        }
        mEnvironments.insert(environment.left(index), environment.mid(index + 1));
    }
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
    if (!mHeaders.isEmpty()) {
        config.writeEntry(u"Headers"_s, mHeaders);
    }
    if (!mEnvironments.isEmpty()) {
        QStringList environments;
        environments.reserve(mEnvironments.count());
        for (auto it = mEnvironments.constBegin(); it != mEnvironments.constEnd(); ++it) {
            environments.append(it.key() + u'=' + it.value());
        }
        config.writeEntry(u"Environments"_s, environments);
    }
}

bool McpProtocolSettings::isValid() const
{
    return (mServerUrl.isValid()) || (!mCommand.isEmpty());
}

QStringList McpProtocolSettings::headers() const
{
    return mHeaders;
}

void McpProtocolSettings::setHeaders(const QStringList &newHeaders)
{
    mHeaders = newHeaders;
}
