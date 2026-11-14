/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpexportclaudecode.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"

#include <KShell>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpExportClaudeCode::McpExportClaudeCode() = default;

McpExportClaudeCode::~McpExportClaudeCode() = default;

bool McpExportClaudeCode::isValid() const
{
    return mServer.isValid() && !mPath.isEmpty();
}

void McpExportClaudeCode::setServer(const McpServer &server)
{
    mServer = server;
}

void McpExportClaudeCode::setPath(const QString &path)
{
    mPath = path;
}

bool McpExportClaudeCode::exportServer() const
{
    if (!isValid()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid server or empty path";
        return false;
    }

    QJsonObject serverObj;
    switch (mServer.transportType()) {
    case McpProtocolPlugin::TransportType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Unknown TransportType it's a bug";
        return false;
    case McpProtocolPlugin::TransportType::Sse:
        serverObj = exportSseSettings();
        break;
    case McpProtocolPlugin::TransportType::Stdio:
        serverObj = exportStdioSettings();
        break;
    case McpProtocolPlugin::TransportType::StreamableHttp:
        serverObj = exportStreamableHttpSettings();
        break;
    }
    if (serverObj.isEmpty()) {
        return false;
    }

    // Keep the other entries of an existing config file (other servers, other settings)
    QJsonObject root;
    QFile existingFile(mPath);
    if (existingFile.exists()) {
        if (!existingFile.open(QIODevice::ReadOnly)) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Impossible to open" << mPath << existingFile.errorString();
            return false;
        }
        const QByteArray data = existingFile.readAll();
        existingFile.close();
        if (!data.trimmed().isEmpty()) {
            QJsonParseError parseError;
            const QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
            if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
                qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid json file, don't overwrite it" << mPath << parseError.errorString();
                return false;
            }
            root = doc.object();
        }
    }

    QJsonObject mcpServers = root.value("mcpServers"_L1).toObject();
    mcpServers[mServer.name()] = serverObj;
    root["mcpServers"_L1] = mcpServers;

    QSaveFile file(mPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Impossible to open" << mPath << file.errorString();
        return false;
    }
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    if (!file.commit()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Impossible to save" << mPath << file.errorString();
        return false;
    }
    return true;
}

QJsonObject McpExportClaudeCode::exportStdioSettings() const
{
    const McpProtocolSettings settings = mServer.settings();
    QJsonObject obj;
    obj["type"_L1] = u"stdio"_s;
    obj["command"_L1] = settings.command();

    KShell::Errors splitError = KShell::NoError;
    const QStringList arguments = KShell::splitArgs(settings.arguments(), KShell::NoOptions, &splitError);
    if (splitError != KShell::NoError) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid arguments, impossible to export server";
        return {};
    }
    if (!arguments.isEmpty()) {
        obj["args"_L1] = QJsonArray::fromStringList(arguments);
    }

    const QMap<QString, QString> environments = settings.environments();
    if (!environments.isEmpty()) {
        QJsonObject env;
        for (auto i = environments.cbegin(), end = environments.cend(); i != end; ++i) {
            env[i.key()] = i.value();
        }
        obj["env"_L1] = env;
    }
    return obj;
}

QJsonObject McpExportClaudeCode::exportSseSettings() const
{
    return exportUrlSettings(u"sse"_s);
}

QJsonObject McpExportClaudeCode::exportStreamableHttpSettings() const
{
    return exportUrlSettings(u"http"_s);
}

QJsonObject McpExportClaudeCode::exportUrlSettings(const QString &type) const
{
    const McpProtocolSettings settings = mServer.settings();
    QJsonObject obj;
    obj["type"_L1] = type;
    obj["url"_L1] = settings.serverUrl().toString();

    QJsonObject headers;
    const QStringList headerList = settings.headers();
    for (const QString &header : headerList) {
        // Same format as McpClientUtils::addHeaders: "Name: Value"
        const qsizetype index = header.indexOf(u':');
        if (index <= 0) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid header, expected \"Name: Value\"";
            continue;
        }
        headers[header.left(index).trimmed()] = header.mid(index + 1).trimmed();
    }
    if (!settings.authToken().isEmpty()) {
        // We must export token. We allow to use export env.
        headers["Authorization"_L1] = u"Bearer ${MCP_AUTH_TOKEN}"_s;
    }
    if (!headers.isEmpty()) {
        obj["headers"_L1] = headers;
    }
    return obj;
}
