/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpimportclaudecode.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"

#include <KShell>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpImportClaudeCode::McpImportClaudeCode() = default;

McpImportClaudeCode::~McpImportClaudeCode() = default;

QString McpImportClaudeCode::path() const
{
    return mPath;
}

void McpImportClaudeCode::setPath(const QString &newPath)
{
    mPath = newPath;
}

bool McpImportClaudeCode::importServer()
{
    mMcpServers.clear();
    if (mPath.isEmpty()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "mPath is empty";
        return false;
    }
    QFile f(mPath);
    if (!f.open(QIODevice::ReadOnly)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Impossible to open file:" << mPath << f.errorString();
        return false;
    }
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid json file:" << mPath << parseError.errorString();
        return false;
    }
    const QJsonObject serversObj = doc.object().value("mcpServers"_L1).toObject();
    if (serversObj.isEmpty()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "No mcpServers found in" << mPath;
        return false;
    }

    for (auto it = serversObj.constBegin(), end = serversObj.constEnd(); it != end; ++it) {
        const QJsonObject obj = it.value().toObject();
        QString type = obj.value("type"_L1).toString();
        if (type.isEmpty()) {
            // "type" is optional: Claude Code uses stdio by default
            type = obj.contains("url"_L1) ? u"http"_s : u"stdio"_s;
        }

        McpServer server;
        server.setName(it.key());
        server.createUniqueIdentifier();
        if (type == "stdio"_L1) {
            importStdio(obj, server);
        } else if (type == "sse"_L1) {
            importSse(obj, server);
        } else if (type == "http"_L1 || type == "streamable-http"_L1) {
            importStreamableHttp(obj, server);
        } else {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Unknown server type" << type << "for" << it.key();
            continue;
        }
        if (!server.isValid()) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid server, skip it:" << it.key();
            continue;
        }
        mMcpServers.append(server);
    }
    return !mMcpServers.isEmpty();
}

void McpImportClaudeCode::importStdio(const QJsonObject &obj, McpServer &server) const
{
    server.setTransportType(McpProtocolPlugin::TransportType::Stdio);
    McpProtocolSettings settings;
    settings.setCommand(obj.value("command"_L1).toString());

    QStringList arguments;
    const QJsonArray args = obj.value("args"_L1).toArray();
    arguments.reserve(args.count());
    for (const auto &arg : args) {
        arguments.append(arg.toString());
    }
    if (!arguments.isEmpty()) {
        settings.setArguments(KShell::joinArgs(arguments));
    }

    QMap<QString, QString> environments;
    const QJsonObject env = obj.value("env"_L1).toObject();
    for (auto it = env.constBegin(), end = env.constEnd(); it != end; ++it) {
        environments.insert(it.key(), it.value().toString());
    }
    settings.setEnvironments(environments);
    server.setSettings(settings);
}

void McpImportClaudeCode::importSse(const QJsonObject &obj, McpServer &server) const
{
    server.setTransportType(McpProtocolPlugin::TransportType::Sse);
    server.setSettings(importUrlSettings(obj));
}

void McpImportClaudeCode::importStreamableHttp(const QJsonObject &obj, McpServer &server) const
{
    server.setTransportType(McpProtocolPlugin::TransportType::StreamableHttp);
    server.setSettings(importUrlSettings(obj));
}

McpProtocolSettings McpImportClaudeCode::importUrlSettings(const QJsonObject &obj) const
{
    McpProtocolSettings settings;
    settings.setServerUrl(QUrl(obj.value("url"_L1).toString()));

    QStringList headers;
    const QJsonObject headersObj = obj.value("headers"_L1).toObject();
    for (auto it = headersObj.constBegin(), end = headersObj.constEnd(); it != end; ++it) {
        const QString value = it.value().toString();
        if (it.key().compare("Authorization"_L1, Qt::CaseInsensitive) == 0 && value.startsWith("Bearer "_L1)) {
            const QString token = value.mid(7).trimmed();
            // "${VAR}" is an environment variable expanded by Claude Code, we can't use it
            if (!token.isEmpty() && !token.contains("${"_L1)) {
                settings.setAuthToken(token.toUtf8());
            }
            continue;
        }
        // Same format as McpClientUtils::addHeaders: "Name: Value"
        headers.append(it.key() + u": "_s + value);
    }
    settings.setHeaders(headers);
    return settings;
}

QList<McpServer> McpImportClaudeCode::mcpServers() const
{
    return mMcpServers;
}
