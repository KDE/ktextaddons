/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverutils.h"
#include "common/mcpprotocolcommonutils.h"
#include "common/mcpprotocolkeychainutils.h"
#include "common/mcpprotocolsettings.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QTextStream>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
#include <TextUtils/TextUtilsColorShell>
#include <algorithm>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
const char myLocalServerGroupName[] = "Local Server";
const char myHasAuthTokenKey[] = "HasAuthToken";
}

QByteArray McpProtocolServerUtils::generateAuthToken()
{
    return McpProtocolCommonUtils::generateAuthToken();
}

QByteArray McpProtocolServerUtils::authTokenIdentifier(const QString &configName)
{
    // Keep the historical identifier for the default server
    if (configName.isEmpty() || configName == McpProtocolCommonUtils::serverConfigFileName()) {
        return "mcp-server"_ba;
    }
    return "mcp-server-"_ba + configName.toUtf8();
}

void McpProtocolServerUtils::writeAuthToken(const QByteArray &token, const QString &configName)
{
    McpProtocolKeychainUtils::writeAuthToken(authTokenIdentifier(configName), token);
}

void McpProtocolServerUtils::readAuthToken(QObject *context, std::function<void(const QByteArray &)> callback, const QString &configName)
{
    McpProtocolKeychainUtils::readAuthToken(authTokenIdentifier(configName), context, std::move(callback));
}

void McpProtocolServerUtils::removeAuthToken(const QString &configName)
{
    McpProtocolKeychainUtils::removeAuthToken(authTokenIdentifier(configName));
}

QUrl McpProtocolServerUtils::defaultServerUrl()
{
    return QUrl(u"http://127.0.0.1:8765/mcp"_s);
}

void McpProtocolServerUtils::loadSettings(QObject *context, std::function<void(const McpProtocolSettings &)> callback)
{
    loadSettings(KSharedConfig::openConfig(McpProtocolCommonUtils::serverConfigFileName()), context, std::move(callback));
}

void McpProtocolServerUtils::loadSettings(const KSharedConfig::Ptr &config, QObject *context, std::function<void(const McpProtocolSettings &)> callback)
{
    const KConfigGroup group(config, QLatin1StringView(myLocalServerGroupName));
    McpProtocolSettings settings;
    settings.load(group);
    if (settings.serverUrl().isEmpty()) {
        settings.setServerUrl(defaultServerUrl());
    }
    if (!group.readEntry(myHasAuthTokenKey, false)) {
        callback(settings);
        return;
    }
    readAuthToken(
        context,
        [settings, callback = std::move(callback)](const QByteArray &token) mutable {
            settings.setAuthToken(token);
            callback(settings);
        },
        config->name());
}

void McpProtocolServerUtils::saveSettings(const KSharedConfig::Ptr &config, const McpProtocolSettings &settings)
{
    KConfigGroup group(config, QLatin1StringView(myLocalServerGroupName));
    const bool hadAuthToken = group.readEntry(myHasAuthTokenKey, false);
    group.deleteGroup();
    settings.save(group);
    const QByteArray token = settings.authToken();
    if (!token.isEmpty()) {
        group.writeEntry(myHasAuthTokenKey, true);
        writeAuthToken(token, config->name());
    } else if (hadAuthToken) {
        removeAuthToken(config->name());
    }
    config->sync();
}

void McpProtocolServerUtils::saveSettings(const McpProtocolSettings &settings)
{
    saveSettings(KSharedConfig::openConfig(McpProtocolCommonUtils::serverConfigFileName()), settings);
}

void McpProtocolServerUtils::printTools(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTool> &lst)
{
    struct ToolInfo {
        QString groupName;
        QString groupTitle;
        QString toolName;
        QString description;
    };

    QList<ToolInfo> toolInfoLst;
    toolInfoLst.reserve(lst.count());

    qsizetype nameWidth = 0;
    for (const auto &tool : lst) {
        ToolInfo i;
        i.toolName = tool.name();
        i.description = tool.description().value_or(tool.title().value_or(QString()));

        nameWidth = std::max(nameWidth, i.toolName.size());

        if (const auto meta = tool.meta(); meta.has_value() && meta->meta().has_value()) {
            const auto values = *meta->meta();
            i.groupName = values.value(McpProtocolCommonUtils::metaGroupName()).toString();
            i.groupTitle = values.value(McpProtocolCommonUtils::metaGroupTitle()).toString();
        }
        toolInfoLst.append(std::move(i));
    }

    // Tools without group first, then tools grouped by _meta group
    std::sort(toolInfoLst.begin(), toolInfoLst.end(), [](const ToolInfo &left, const ToolInfo &right) {
        return std::tie(left.groupName, left.toolName) < std::tie(right.groupName, right.toolName);
    });

    QTextStream out(stdout);
    out << TextUtils::TextUtilsColorShell::bold(i18n("List of Tools:")) << '\n';

    QString currentGroupName;
    for (const auto &tool : toolInfoLst) {
        if (tool.groupName != currentGroupName) {
            currentGroupName = tool.groupName;
            out << "   " << TextUtils::TextUtilsColorShell::cyan(tool.groupTitle.isEmpty() ? tool.groupName : tool.groupTitle) << '\n';
        }
        out << "      " << TextUtils::TextUtilsColorShell::bold(tool.toolName.leftJustified(nameWidth)) << "   " << tool.description << '\n';
    }
}
