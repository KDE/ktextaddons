/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolsutils.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
using namespace Qt::Literals::StringLiterals;
bool TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::isServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier)
{
    const KConfigGroup group(KSharedConfig::openConfig(serverConfigFileName), u"ToolConfirmation"_s);
    return group.readEntry("AlwaysAllowedServers", QStringList()).contains(QString::fromLatin1(serverIdentifier));
}

void TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::setServerAlwaysAllowed(const QString &serverConfigFileName,
                                                                                 const QByteArray &serverIdentifier,
                                                                                 bool allowed)
{
    KConfigGroup group(KSharedConfig::openConfig(serverConfigFileName), u"ToolConfirmation"_s);
    QStringList servers = group.readEntry("AlwaysAllowedServers", QStringList());
    const QString identifier = QString::fromLatin1(serverIdentifier);
    servers.removeAll(identifier);
    if (allowed) {
        servers.append(identifier);
    }
    group.writeEntry("AlwaysAllowedServers", servers);
    group.sync();
}

QList<QByteArray> TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::alwaysAllowedServers(const QString &serverConfigFileName)
{
    const KConfigGroup group(KSharedConfig::openConfig(serverConfigFileName), u"ToolConfirmation"_s);
    const QStringList servers = group.readEntry("AlwaysAllowedServers", QStringList());
    QList<QByteArray> identifiers;
    identifiers.reserve(servers.count());
    for (const QString &server : servers) {
        identifiers.append(server.toLatin1());
    }
    return identifiers;
}

void TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::setAlwaysAllowedServers(const QString &serverConfigFileName,
                                                                                  const QList<QByteArray> &serverIdentifiers)
{
    QStringList servers;
    servers.reserve(serverIdentifiers.count());
    for (const QByteArray &identifier : serverIdentifiers) {
        servers.append(QString::fromLatin1(identifier));
    }
    KConfigGroup group(KSharedConfig::openConfig(serverConfigFileName), u"ToolConfirmation"_s);
    group.writeEntry("AlwaysAllowedServers", servers);
    group.sync();
}

bool TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::sameConnectionSettings(TextAutoGenerateTextMcpProtocolCore::McpServer first,
                                                                                 TextAutoGenerateTextMcpProtocolCore::McpServer second)
{
    first.setFilterTools(false);
    first.setAllowedTools({});
    second.setFilterTools(false);
    second.setAllowedTools({});
    return first == second;
}

QString TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::toolRiskIconName(TextAutoGenerateMcpToolsManager::ToolRisk risk)
{
    switch (risk) {
    case TextAutoGenerateMcpToolsManager::ToolRisk::ReadOnly:
        return u"security-high"_s;
    case TextAutoGenerateMcpToolsManager::ToolRisk::Modify:
        return u"security-medium"_s;
    case TextAutoGenerateMcpToolsManager::ToolRisk::Destructive:
        return u"security-low"_s;
    }
    return {};
}

QString TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::toolRiskText(TextAutoGenerateMcpToolsManager::ToolRisk risk)
{
    switch (risk) {
    case TextAutoGenerateMcpToolsManager::ToolRisk::ReadOnly:
        return i18n("Read-only");
    case TextAutoGenerateMcpToolsManager::ToolRisk::Modify:
        return i18n("Modifies data");
    case TextAutoGenerateMcpToolsManager::ToolRisk::Destructive:
        return i18n("May delete or overwrite data");
    }
    return {};
}
